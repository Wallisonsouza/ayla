#include "ayla-semantic/ayla-resolver/Resolver.hpp"

void Resolver::resolve_binary_expression(parser::node::BinaryExpressionNode *node) {
  resolve(node->lhs);
  resolve(node->rhs);
}
