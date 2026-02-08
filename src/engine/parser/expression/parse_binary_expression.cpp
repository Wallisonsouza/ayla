#include "engine/parser/parser.hpp"
#include "frontend/ast/expressions/BinaryExpressionNode.hpp"

ayla::ast::ExpressionNode *Parser::parse_binary_expression(int min_bp, ayla::ast::ExpressionNode *left) {
  if (!left) return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok) break;

    auto info = unit.context.precedence_table.get(tok->descriptor->kind);

    if (!info || info->lbp < min_bp) break;

    unit.tokens.advance();

    auto *right = parse_unary_expression();
    if (!right) return nullptr;

    right = parse_binary_expression(info->rbp, right);

    left = unit.ast.create_node<ayla::ast::node::BinaryExpressionNode>(left, info->op, right);
  }

  return left;
}
