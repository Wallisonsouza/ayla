#include "ExpressionParser.hpp"

#include "Parser.hpp"
#include "ParserContext.hpp"

#include "ast/expressions/AssignmentExpression.hpp"
#include "ast/expressions/BinaryExpressionNode.hpp"
#include "ast/expressions/CallExpressionNode.hpp"
#include "ast/expressions/IndexAcessExpressionNode.hpp"
#include "ast/expressions/LiteralExpressionNode.hpp"
#include "ast/expressions/MemberAccessExpressionNode.hpp"
#include "ast/expressions/UnaryExpressionNode.hpp"

#include "NameParser.hpp"
#include "core/token/Token.hpp"
#include "syntax/parser/ParserUtil.hpp"
#include <iostream>

ExpressionParser::ExpressionParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

ayla::ast::ExpressionNode *ExpressionParser::parse_member_access(ayla::ast::ExpressionNode *base) {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::DOT)) return nullptr;

  auto *member = parser.names().parse_name();

  if (!member) return nullptr;

  return context.ast().create_node<ayla::ast::node::MemberAccessExpressionNode>(base, member);
}

ayla::ast::ExpressionNode *ExpressionParser::parse_index_access(ayla::ast::ExpressionNode *base) {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::OPEN_BRACKET)) return nullptr;

  auto *index = parse_expression();

  if (!index) return nullptr;

  if (!tokens.match(TokenKind::CLOSE_BRACKET)) return nullptr;

  return context.ast().create_node<ayla::ast::node::IndexAccessExpressionNode>(base, index);
}

ayla::ast::ExpressionNode *ExpressionParser::parse_call(ayla::ast::ExpressionNode *callee) {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::OPEN_PAREN)) return nullptr;

  std::vector<ayla::ast::ExpressionNode *> args;

  while (!tokens.is_end() && !tokens.match(TokenKind::CLOSE_PAREN)) {

    auto *expr = parse_expression();

    if (!expr) return nullptr;

    args.push_back(expr);

    if (!tokens.match(TokenKind::COMMA)) {
      if (!tokens.match(TokenKind::CLOSE_PAREN)) return nullptr;

      break;
    }
  }

  return context.ast().create_node<ayla::ast::node::CallExpressionNode>(callee, std::move(args));
}

ayla::ast::ExpressionNode *ExpressionParser::parse_number_literal() {
  auto &tokens = context.tokens();

  auto *token = tokens.match(TokenKind::NUMBER_LITERAL);

  if (!token) return nullptr;

  auto text = context.source().buffer.get_text(token->slice.span);

  try {
    return context.ast().create_node<ayla::ast::node::NumberLiteralNode>(std::stod(text));
  } catch (...) { return nullptr; }
}

ayla::ast::ExpressionNode *ExpressionParser::parse_string_literal() {
  auto *token = context.tokens().match(TokenKind::STRING_LITERAL);

  if (!token) return nullptr;

  auto text = context.source().buffer.get_text(token->slice.span);

  return context.ast().create_node<ayla::ast::node::StringLiteralNode>(text);
}

ayla::ast::ExpressionNode *ExpressionParser::parse_bool_literal() {
  auto *token = context.tokens().advance();

  if (!token) return nullptr;

  bool value = token->descriptor->kind == TokenKind::TRUE;

  return context.ast().create_node<ayla::ast::node::BoolLiteralNode>(value);
}

ayla::ast::ExpressionNode *ExpressionParser::parse_assignment(ayla::ast::ExpressionNode *target) {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::ASSIGN)) return nullptr;

  auto *value = parse_expression();

  if (!value) return nullptr;

  return context.ast().create_node<ayla::ast::node::AssignmentExpressionNode>(target, value);
}

ayla::ast::ExpressionNode *ExpressionParser::parse_binary_expression(int min_bp, ayla::ast::ExpressionNode *left) {
  if (!left) return nullptr;

  while (true) {
    auto *token = context.tokens().peek();

    if (!token) break;

    auto info = context.precedence().get(token->descriptor->kind);

    if (!info || info->lbp < min_bp) break;

    context.tokens().advance();

    auto *right = parse_unary_expression();

    if (!right) return nullptr;

    right = parse_binary_expression(info->rbp, right);

    left = context.ast().create_node<ayla::ast::node::BinaryExpressionNode>(left, info->op, right);
  }

  return left;
}

ayla::ast::ExpressionNode *ExpressionParser::parse_expression() {
  auto *lhs = parse_unary_expression();

  if (!lhs) return nullptr;

  if (auto *assign = parse_assignment(lhs)) { return assign; }

  return parse_binary_expression(0, lhs);
}

ayla::ast::ExpressionNode *ExpressionParser::parse_grouped_expression() {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::OPEN_PAREN)) return nullptr;

  auto *expr = parse_expression();

  if (!expr) return nullptr;

  if (!tokens.match(TokenKind::CLOSE_PAREN)) return nullptr;

  return expr;
}

ayla::ast::ExpressionNode *ExpressionParser::parse_postfix_expression() {
  auto *expr = parse_primary_expression();

  if (!expr) return nullptr;

  while (true) {
    auto *token = context.tokens().peek();

    if (!token) break;

    switch (token->descriptor->kind) {

    case TokenKind::OPEN_PAREN: expr = parse_call(expr); break;

    case TokenKind::DOT: expr = parse_member_access(expr); break;

    case TokenKind::OPEN_BRACKET: expr = parse_index_access(expr); break;

    default: return expr;
    }

    if (!expr) return nullptr;
  }

  return expr;
}

ayla::ast::ExpressionNode *ExpressionParser::parse_primary_expression() {
  auto *token = context.tokens().peek();

  if (!token) return nullptr;

  switch (token->descriptor->kind) {

  case TokenKind::NUMBER_LITERAL: return parse_number_literal();

  case TokenKind::STRING_LITERAL: return parse_string_literal();

  case TokenKind::TRUE:
  case TokenKind::FALSE: return parse_bool_literal();

  case TokenKind::IDENTIFIER: return parse_identifier_expression();

  case TokenKind::OPEN_PAREN: return parse_grouped_expression();

  default: return nullptr;
  }
}

ayla::ast::ExpressionNode *ExpressionParser::parse_identifier_expression() {

  std::cout << "method parse_identifier_expression not implemented";

  return nullptr;
}

ayla::ast::ExpressionNode *ExpressionParser::parse_unary_expression() {
  auto *token = context.tokens().peek();

  if (!token) return parse_postfix_expression();

  UnaryOperation op;

  switch (token->descriptor->kind) {

  case TokenKind::NOT: op = UnaryOperation::Not; break;

  default: return parse_postfix_expression();
  }

  context.tokens().advance();

  auto *operand = parse_unary_expression();

  return context.ast().create_node<ayla::ast::node::UnaryExpressionNode>(op, operand);
}