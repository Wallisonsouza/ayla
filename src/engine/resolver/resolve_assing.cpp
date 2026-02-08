#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_assignment(ayla::ast::node::AssignmentExpressionNode *node) {

  if (node->target) { resolve(node->target); }

  if (node->value) { resolve(node->value); }
}
