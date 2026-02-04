#include "core/node/Type.hpp"
#include "engine/resolver/Resolver.hpp"

inline void Resolver::resolve_type(core::ast::TypeNode *node) {
  
  if (!node || !node->identifier) return;

  resolve(node->identifier);

  auto sym = current_scope->resolve_symbol(node->identifier->name);
  if (!sym.is_valid()) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->identifier->slice, {{"name", node->identifier->name}});
    node->symbol_id = INVALID_SYMBOL_ID;
    return;
  }

  node->symbol_id = sym;

  for (auto *generic : node->generics) { resolve_type(generic); }
}
