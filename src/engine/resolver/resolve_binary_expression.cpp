#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_binary_expression(ayla::ast::node::BinaryExpressionNode *node) {
  resolve(node->lhs);
  resolve(node->rhs);
}
