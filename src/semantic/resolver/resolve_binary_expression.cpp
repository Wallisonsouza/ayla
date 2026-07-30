#include "ast/expressions/UnaryExpressionNode.hpp"
#include "semantic/resolver/Resolver.hpp"

void Resolver::binary_expression(ayla::ast::node::BinaryExpressionNode *node) {
  resolve(node->lhs);
  resolve(node->rhs);
}

void Resolver::unary_expression(ayla::ast::node::UnaryExpressionNode *node) {
  //
  if (node->operand) { resolve(node->operand); }
}