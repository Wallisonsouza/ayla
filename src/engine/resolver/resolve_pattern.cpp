#include "Resolver.hpp"
#include "core/memory/BuiltinTypes.hpp"
#include "core/node/Type.hpp"

void Resolver::resolve_pattern(ayla::ast::PatternNode *pat) {
  if (!pat) return;

  switch (pat->kind) {

  case ayla::ast::NodeKind::IdentifierPattern: {

    auto *pattern = static_cast<ayla::ast::IdentifierPatternNode *>(pat);

    if (current_scope->has_symbol_local(pattern->identifier->name)) {

      report_error(DiagnosticCode::RedeclaredIdentifier, pattern->identifier->slice, {{"name", pattern->identifier->name}});
      return;
    }

    SymbolId sym = unit.context.symbol_manager.create_symbol(pattern->identifier->name, SymbolKind::Variable, Visibility::Private, false, pat);

    current_scope->declare(pattern->identifier->name, sym);

    pattern->symbol_id = sym;

    if (pattern->type_annotation) resolve_type_node(pattern->type_annotation);

    break;
  }

  default: break;
  }
}