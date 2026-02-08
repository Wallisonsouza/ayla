#include "engine/parser/parser.hpp"
#include "frontend/ast/ExpressionNode.hpp"
#include "frontend/ast/expressions/UnaryExpressionNode.hpp"

ayla::ast::ExpressionNode *Parser::parse_unary_expression() {
  auto *tok = unit.tokens.peek();
  if (!tok) return parse_postfix_expression();

  ayla::UnaryOperation op;

  switch (tok->descriptor->kind) {
  case TokenKind::NOT:
    op = ayla::UnaryOperation::NOT;
    break;

    // case TokenKind::MINUS: op = ayla::UnaryOperation::NEGATE; break;

  default: return parse_postfix_expression();
  }

  unit.tokens.advance();

  auto *operand = parse_unary_expression(); // recursivo!

  return unit.ast.create_node<ayla::ast::node::UnaryExpressionNode>(op, operand);
}
