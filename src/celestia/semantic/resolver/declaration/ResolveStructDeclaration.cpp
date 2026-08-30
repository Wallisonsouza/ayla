#include "celestia/semantic/resolver/Resolver.hpp"

namespace celestia::semantic {

void Resolver::resolve_struct_declaration(ast::StructDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  SymbolId symbol_id = declare_symbol(name, SymbolKind::Type, node->specifiers.visibility, node);

  if (!symbol_id.is_valid()) return;

  auto *struct_scope = context.scope_manager.create_scope(core::ScopeKind::Struct, context.scopes.current());

  if (!struct_scope) return;

  context.scopes.push(*struct_scope);

  // struct<T1, T2, ...>
  declare_generics(node->generic_parameters);

  // struct<T> : Type<T>, ... — resolve all composed/base types.
  for (auto *composition : node->compositions) {

    if (composition) resolve(composition);
  }

  // struct Foo<T> { value: T }
  for (auto *field : node->fields) {

    if (field) resolve(field);
  }

  context.scopes.pop();
}
} // namespace celestia::semantic