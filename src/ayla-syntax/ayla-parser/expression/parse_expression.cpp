#include "ayla-syntax/ayla-parser/parser.hpp"

core::ast::ASTExpressionNode *Parser::parse_expression() {

  auto *lhs = parse_postfix_expression();
  if (!lhs) return nullptr;

  if (auto *assign = parse_assignment(lhs)) return assign;

  return parse_binary_expression(0, lhs);
}

core::ast::ASTExpressionNode *Parser::parse_grouped_expression() {

  auto *open = unit.tokens.match(TokenKind::OPEN_PAREN);
  if (!open) return nullptr;

  core::ast::ASTExpressionNode *expr = parse_expression();
  if (!expr) { return nullptr; }

  auto *close = unit.tokens.match(TokenKind::CLOSE_PAREN);
  if (!close) { return nullptr; }

  return expr;
}