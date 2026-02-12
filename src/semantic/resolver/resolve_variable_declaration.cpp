#include "Resolver.hpp"
#include "ast/statements/VariableDeclarationNode.hpp"
#include "core/node/Modifier.hpp"

void Resolver::resolve_variable_declaration(ayla::ast::node::VariableDeclarationNode *node) {

  if (node->pattern) { resolve_pattern(node->pattern, node->modifiers); }

  if (node->initializer) { resolve(node->initializer); }
}
