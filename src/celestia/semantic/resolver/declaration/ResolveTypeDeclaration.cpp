#include "celestia/semantic/resolver/Resolver.hpp"

namespace celestia::semantic {

void Resolver::resolve_type_declaration(ast::TypeDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  SymbolId symbol_id = declare_symbol(name, SymbolKind::Type, node->specifiers.visibility, node);

  if (!symbol_id.is_valid()) return;

  auto *type_scope = context.scope_manager.create_scope(core::ScopeKind::Type, context.scopes.current());

  if (!type_scope) return;

  context.scopes.push(*type_scope);

  declare_generics(node->generic_parameters);

  context.scopes.pop();
}

} // namespace celestia::semantic