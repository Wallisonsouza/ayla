#include "Resolver.hpp"
#include "core/node/Modifier.hpp"

void Resolver::resolve_pattern(ayla::ast::PatternNode *pat, ayla::ast::Modifiers modifier) {
  if (!pat) return;

  switch (pat->kind) {
  case ayla::ast::NodeKind::IdentifierPattern: {
    auto *pattern = static_cast<ayla::ast::IdentifierPatternNode *>(pat);

    if (current_scope->has_symbol_local(pattern->identifier->name)) {
      report_error(DiagnosticCode::RedeclaredIdentifier, pattern->identifier->slice, {{"name", pattern->identifier->name}});
      return;
    }

    SymbolId sybol_id = unit.context.symbol_manager.create_symbol(pattern->identifier->name, SymbolKind::Variable, Visibility::Private, false, pat);

    auto symbol = unit.context.symbol_manager.get(sybol_id);
    symbol->modifiers = modifier;

    current_scope->declare(pattern->identifier->name, sybol_id);

    pattern->symbol_id = sybol_id;
    pattern->local_slot = current_scope->resolve_slot(sybol_id).value_or(0);

    pattern->identifier->resolved_symbol_id = pattern->symbol_id;
    pattern->identifier->local_slot = pattern->local_slot;

    if (pattern->type_annotation) resolve_type_node(pattern->type_annotation);

    break;
  }

  default: break;
  }
}
