#include "semantic/resolver/Resolver.hpp"

void Resolver::resolve_pattern(ayla::ast::PatternNode *pat, ayla::ast::Modifiers modifier) {
  if (!pat) return;

  switch (pat->kind) {
  case ayla::ast::NodeKind::IdentifierPattern: {
    auto *pattern = static_cast<ayla::ast::IdentifierPatternNode *>(pat);

    // Verifica redeclaração
    if (current_scope->has_symbol_local(pattern->identifier->name)) {
      report_error(DiagnosticCode::RedeclaredIdentifier, pattern->identifier->slice, {{"name", pattern->identifier->name}});
      return;
    }

    // Cria símbolo
    SymbolId symbol_id = unit.context.symbol_manager.create_symbol(pattern->identifier->name, SymbolKind::Variable, Visibility::Private, false, pat);

    auto symbol = unit.context.symbol_manager.get(symbol_id);
    symbol->modifiers = modifier;

    // Declara no scope atual
    current_scope->declare(pattern->identifier->name, symbol_id);

    // Slot da variável: se não houver, aloca temporário
    pattern->symbol_id = symbol_id;
    pattern->local_slot = current_scope->resolve_slot(symbol_id).value_or(0);

    // Atualiza a expressão identificadora associada
    pattern->identifier->resolved_symbol_id = pattern->symbol_id;
    pattern->identifier->local_slot = pattern->local_slot;

    // Resolve tipo se houver anotação
    if (pattern->type_annotation) resolve_type_node(pattern->type_annotation);

    break;
  }

  default:
    break;
  }
}