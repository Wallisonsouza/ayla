
#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/ast/expressions/IdentifierExpressionNode.hpp"
#include "celestia/ast/expressions/LiteralExpressionNode.hpp"
#include "celestia/syntax/parser/expressions/Expression.hpp"
#include "celestia/syntax/parser/NameParser.hpp"
#include "celestia/syntax/parser/Parser.hpp"
#include "celestia/syntax/parser/ParserContext.hpp"
namespace celestia::syntax {
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

celestia::ast::Expression *ExpressionParser::parse_identifier_expression() {
  auto *name = parser.names().parse_name();

  if (!name) return nullptr;

  return context.get_ast().create_node<celestia::ast::IdentifierExpressionNode>(name);
}

celestia::ast::Expression *ExpressionParser::parse_grouped_expression() {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::OPEN_PAREN)) return nullptr;

  auto *expr = parse_expression();

  if (!expr) return nullptr;

  if (!tokens.match(TokenKind::CLOSE_PAREN)) return nullptr;

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
}}