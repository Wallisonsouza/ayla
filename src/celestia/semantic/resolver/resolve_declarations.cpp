#include "Resolver.hpp"
#include "celestia/semantic/resolver/Trace.hpp"
#include <iostream>

namespace celestia::semantic {

void Resolver::resolve_field_declaration(ast::FieldDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  SymbolId symbol_id = declare_symbol(name, SymbolKind::Field, Visibility::Private, node);

  if (!symbol_id.is_valid()) return;

  if (node->type) resolve(node->type);
}

void Resolver::resolve_capability_declaration(ast::CapabilityDeclaration *node) {

  assert(node && "Resolver::resolve_capability_declaration received null");
  assert(node->name && "CapabilityDeclaration has no name");

  const std::string &name = node->name->str;

  debug::trace(debug::Category::Resolver, "resolving capability '{}'", name);

  SymbolId symbol_id = declare_symbol(name, SymbolKind::Capability, node->specifiers.visibility, node);

  if (!symbol_id.is_valid()) return;

  auto *parent_scope = context.scopes.current();

  assert(parent_scope && "Resolver has no active scope while resolving capability");

  auto *capability_scope = context.scope_manager.create_scope(core::ScopeKind::Capability, parent_scope);

  assert(capability_scope && "failed to create capability scope");

  if (!capability_scope) return;

  context.scopes.push(*capability_scope);

  debug::trace(debug::Category::Resolver, "entered capability scope '{}' -> SymbolId({})", name, symbol_id.index());

  // Comparable<T>
  declare_generics(node->generic_parameters);

  // Members
  for (auto *member : node->members) {

    assert(member && "CapabilityDeclaration contains null member");

    resolve(member);
  }

  context.scopes.pop();

  debug::trace(debug::Category::Resolver, "resolved capability '{}'", name);
}

void Resolver::declare_generics(const std::vector<ast::IdentifierNode *> &parameters) {

  for (auto *generic : parameters) {

    if (!generic) continue;

    declare_symbol(generic->str, SymbolKind::Type, Visibility::Private, generic);
  }
}

void Resolver::resolve_impl_declaration(ast::ImplDeclaration *node) {

  if (!node) return;

  std::cout << "Resolvendo[impl]\n";

  auto *impl_scope = context.scope_manager.create_scope(core::ScopeKind::Impl, context.scopes.current());

  if (!impl_scope) return;

  context.scopes.push(*impl_scope);

  declare_generics(node->generic_parameters);

  resolve(node->target);
  resolve(node->capability);

  for (auto *member : node->members) {

    if (member) resolve(member);
  }

  context.scopes.pop();
}

} // namespace celestia::semantic