#include "celestia/semantic/resolver/Resolver.hpp"

namespace celestia::semantic {

void Resolver::resolve_variable_declaration(ast::VariableDeclaration *node) {

  if (!node) return;

  if (node->pattern) pattern(node->pattern, node->specifiers.visibility);

  if (node->initializer) resolve(node->initializer);
}

} // namespace celestia::semantic