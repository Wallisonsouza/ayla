#include "Resolver.hpp"
#include "core/modifiers/ModifierSet.hpp"

void Resolver::resolve_pattern(ayla::ast::PatternNode *pat, ModifierSet modifier) {
  // if (!pat) return;

  // switch (pat->kind) {
  // case ayla::ast::NodeKind::IdentifierPattern: {
  //   auto *pattern = static_cast<ayla::ast::IdentifierPatternNode *>(pat);

  //   if (current_scope->symbols.contains(pattern->name->str)) {
  //     // //report_error(DiagnosticCode::RedeclaredIdentifier, pattern->identifier->slice, {{"name", pattern->identifier->name}});
  //     return;
  //   }

  //   SymbolId sybol_id = unit.context.symbol_manager.create_symbol(pattern->name->str, SymbolKind::Variable, Visibility::Private, false, pat);

  //   auto symbol = unit.context.symbol_manager.get(sybol_id);
  //   symbol->modifiers = modifier;

  //   current_scope->symbols.insert(pattern->name->str, sybol_id);

  //   pattern->symbol_id = sybol_id;

  //   pattern->name->resolved_symbol_id = sybol_id;

  //   if (pattern->type_annotation) resolve_type_node(pattern->type_annotation);

  //   break;
  // }

  // default: break;
  // }
}
