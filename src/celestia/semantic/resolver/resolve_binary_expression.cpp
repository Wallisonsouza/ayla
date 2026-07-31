#include "celestia/ast/expressions/UnaryExpressionNode.hpp"
#include "celestia/semantic/resolver/Resolver.hpp"

void Resolver::binary_expression(celestia::ast::node::BinaryExpressionNode *node) {
  resolve(node->lhs);
  resolve(node->rhs);
}

void Resolver::unary_expression(celestia::ast::node::UnaryExpressionNode *node) {
  //
  if (node->operand) { resolve(node->operand); }
}