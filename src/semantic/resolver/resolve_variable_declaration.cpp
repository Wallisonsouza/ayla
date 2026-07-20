#include "Resolver.hpp"
#include "ast/declarations/VariableDeclarationNode.hpp"

void Resolver::resolve_variable_declaration(ayla::ast::node::VariableDeclarationNode *node) {

  if (node->pattern) { resolve_pattern(node->pattern, node->specifiers.modifiers); }

  if (node->initializer) { resolve(node->initializer); }
}
