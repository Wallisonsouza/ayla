#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_assignment(parser::node::statement::AssignmentNode *node) {

  resolve(node->target);

  resolve(node->value);
}
