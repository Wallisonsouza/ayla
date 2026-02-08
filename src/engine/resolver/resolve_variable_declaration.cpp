#include "Resolver.hpp"
#include "frontend/ast/statements/VariableDeclarationNode.hpp"

void Resolver::resolve_variable_declaration(ayla::ast::node::VariableDeclarationNode *node) {
  if (node->pattern) { resolve_pattern(node->pattern); }

  if (node->initializer) { resolve(node->initializer); }
}