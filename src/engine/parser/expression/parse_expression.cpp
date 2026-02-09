#include "engine/parser/parser.hpp"
#include "frontend/ast/ExpressionNode.hpp"

ayla::ast::ExpressionNode *Parser::parse_expression() {
  auto *lhs = parse_unary_expression();

  if (!lhs) return nullptr;

  if (auto *assign = parse_assignment(lhs)) return assign;

  return parse_binary_expression(0, lhs);
}

ayla::ast::ExpressionNode *Parser::parse_grouped_expression() {

  auto *open = unit.tokens.match(TokenKind::OPEN_PAREN);
  if (!open) return nullptr;

  ayla::ast::ExpressionNode *expr = parse_expression();
  if (!expr) { return nullptr; }

  auto *close = unit.tokens.match(TokenKind::CLOSE_PAREN);
  if (!close) { return nullptr; }

  return expr;
}