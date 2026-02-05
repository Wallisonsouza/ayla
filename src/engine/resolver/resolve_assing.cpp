#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_assignment(ayla::ast::node::AssignmentExpressionNode *node) {

  resolve(node->target);

  resolve(node->value);
}
