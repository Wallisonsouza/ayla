#include "ExpressionParser.hpp"

#include "celestia/syntax/parser/Parser.hpp"
#include "ParserContext.hpp"
#include "NameParser.hpp"
#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/ast/expressions/AssignmentExpression.hpp"
#include "celestia/ast/expressions/BinaryExpressionNode.hpp"
#include "celestia/ast/expressions/CallExpressionNode.hpp"
#include "celestia/ast/expressions/IdentifierExpressionNode.hpp"
#include "celestia/ast/expressions/IndexAcessExpressionNode.hpp"
#include "celestia/ast/expressions/LiteralExpressionNode.hpp"
#include "celestia/ast/expressions/MemberAccessExpressionNode.hpp"
#include "celestia/ast/expressions/UnaryExpressionNode.hpp"
#include "celestia/core/operators/OperatorKind.hpp"
#include <variant>

ExpressionParser::ExpressionParser(ParseContext &context, celestia::Parser &parser) : context(context), parser(parser) {}

celestia::ast::Expression *ExpressionParser::parse_number_literal() {
  auto &tokens = context.tokens();

  auto *token = tokens.match(TokenKind::NUMBER_LITERAL);

  if (!token) return nullptr;

  auto text = context.source().buffer.get_text(token->slice.get_span());

  try {
    return context.get_ast().create_node<celestia::ast::NumberLiteralNode>(std::stod(text));
  } catch (...) { return nullptr; }
}

celestia::ast::Expression *ExpressionParser::parse_string_literal() {
  auto *token = context.tokens().match(TokenKind::STRING_LITERAL);

  if (!token) return nullptr;

  auto text = context.source().buffer.get_text(token->slice.get_span());

  return context.get_ast().create_node<celestia::ast::StringLiteralNode>(text);
}

celestia::ast::Expression *ExpressionParser::parse_bool_literal() {
  auto *token = context.tokens().advance();

  if (!token) return nullptr;

  bool value = token->desc->kind == TokenKind::TRUE;

  return context.get_ast().create_node<celestia::ast::BoolLiteralNode>(value);
}

celestia::ast::Expression *ExpressionParser::parse_assignment(celestia::ast::Expression *target) {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::ASSIGN)) return nullptr;

  auto *value = parse_expression();

  if (!value) return nullptr;

  return context.get_ast().create_node<celestia::ast::AssignmentExpressionNode>(target, value);
}

celestia::ast::Expression *ExpressionParser::parse_identifier_expression() {
  auto *name = parser.names().parse_name();

  if (!name) return nullptr;

  return context.get_ast().create_node<celestia::ast::IdentifierExpressionNode>(name);
}

celestia::ast::Expression *ExpressionParser::parse_member_access(celestia::ast::Expression *base) {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::DOT)) return nullptr;

  auto *member = parser.names().parse_name();

  if (!member) return nullptr;

  return context.get_ast().create_node<celestia::ast::MemberAccessExpressionNode>(base, member);
}

celestia::ast::Expression *ExpressionParser::parse_index_access(celestia::ast::Expression *base) {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::OPEN_BRACKET)) return nullptr;

  auto *index = parse_expression();

  if (!index) return nullptr;

  if (!tokens.match(TokenKind::CLOSE_BRACKET)) return nullptr;

  return context.get_ast().create_node<celestia::ast::IndexAccessExpressionNode>(base, index);
}

celestia::ast::Expression *ExpressionParser::parse_call(celestia::ast::Expression *callee) {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::OPEN_PAREN)) return nullptr;

  std::vector<celestia::ast::Expression *> args;

  while (!tokens.is_end()) {
    if (tokens.match(TokenKind::CLOSE_PAREN)) break;

    auto *expr = parse_expression();

    if (!expr) return nullptr;

    args.push_back(expr);

    if (!tokens.match(TokenKind::COMMA)) {
      if (!tokens.match(TokenKind::CLOSE_PAREN)) return nullptr;

      break;
    }
  }

  return context.get_ast().create_node<celestia::ast::CallExpressionNode>(callee, std::move(args));
}

celestia::ast::Expression *ExpressionParser::parse_binary_expression(int min_bp, celestia::ast::Expression *left) {
  while (true) {
    auto *token = context.tokens().peek();

    if (!token) break;

    auto *info = context.operators().get(token->desc->kind);

    if (!info || info->kind != core::OperatorKind::Infix) break;

    if (info->lbp < min_bp) break;

    if (!std::holds_alternative<BinaryOperation>(info->op)) return nullptr;

    context.tokens().advance();

    auto *right = parse_unary_expression();

    if (!right) return nullptr;

    right = parse_binary_expression(info->rbp, right);

    auto op = std::get<BinaryOperation>(info->op);

    left = context.get_ast().create_node<celestia::ast::BinaryExpressionNode>(left, op, right);
  }

  return left;
}

celestia::ast::Expression *ExpressionParser::parse_grouped_expression() {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::OPEN_PAREN)) return nullptr;

  auto *expr = parse_expression();

  if (!expr) return nullptr;

  if (!tokens.match(TokenKind::CLOSE_PAREN)) return nullptr;

  return expr;
}

celestia::ast::Expression *ExpressionParser::parse_postfix_expression() {
  auto *expr = parse_primary_expression();

  if (!expr) return nullptr;

  while (true) {
    auto *token = context.tokens().peek();

    if (!token) break;

    auto *info = context.operators().get(token->desc->kind);

    if (!info || info->kind != core::OperatorKind::Postfix) break;

    if (!std::holds_alternative<PostfixOperation>(info->op)) return nullptr;

    context.tokens().advance();

    auto op = std::get<PostfixOperation>(info->op);

    switch (op) {
    case PostfixOperation::Call: expr = parse_call(expr); break;

    case PostfixOperation::IndexAccess: expr = parse_index_access(expr); break;

    case PostfixOperation::MemberAccess: expr = parse_member_access(expr); break;
    }

    if (!expr) return nullptr;
  }

  return expr;
}

celestia::ast::Expression *ExpressionParser::parse_primary_expression() {
  auto *token = context.tokens().peek();

  if (!token) return nullptr;

  switch (token->desc->kind) {
  case TokenKind::NUMBER_LITERAL: return parse_number_literal();

  case TokenKind::STRING_LITERAL: return parse_string_literal();

  case TokenKind::TRUE:
  case TokenKind::FALSE: return parse_bool_literal();

  case TokenKind::IDENTIFIER: return parse_identifier_expression();

  case TokenKind::OPEN_PAREN: return parse_grouped_expression();

  default: return nullptr;
  }
}

celestia::ast::Expression *ExpressionParser::parse_unary_expression() {
  auto *token = context.tokens().peek();

  if (!token) return parse_postfix_expression();

  auto *info = context.operators().get(token->desc->kind);

  if (!info || info->kind != core::OperatorKind::Prefix) { return parse_postfix_expression(); }

  if (!std::holds_alternative<UnaryOperation>(info->op)) return nullptr;

  context.tokens().advance();

  auto op = std::get<UnaryOperation>(info->op);

  auto *operand = parse_unary_expression();

  if (!operand) return nullptr;

  return context.get_ast().create_node<celestia::ast::UnaryExpressionNode>(op, operand);
}

celestia::ast::Expression *ExpressionParser::parse_expression() {
  auto *lhs = parse_unary_expression();

  if (!lhs) return nullptr;

  return parse_binary_expression(0, lhs);
}
