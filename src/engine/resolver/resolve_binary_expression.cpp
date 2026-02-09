#include "engine/resolver/Resolver.hpp"
#include "frontend/ast/expressions/UnaryExpressionNode.hpp"

void Resolver::resolve_binary_expression(ayla::ast::node::BinaryExpressionNode *node) {
  resolve(node->lhs);
  resolve(node->rhs);
}

void Resolver::resolve_unary_expression(ayla::ast::node::UnaryExpressionNode *node) {
  //
  if (node->operand) { resolve(node->operand); }
}