#include "core/memory/BuiltinTypes.hpp"
#include "core/node/Type.hpp"
#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_identifier(core::ast::IdentifierNode *node) {

  SymbolId id = current_scope->resolve_symbol(node->name);

  if (!id.is_valid()) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->slice);
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  node->resolved_symbol_id = id;

  Symbol *sym = unit.symbols.get(id);

  if (sym) { node->inferred_type = sym->type; }
}
