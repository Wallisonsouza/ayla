#include "Resolver.hpp"
#include "ast/NodeKind.hpp"


void Resolver::resolve_identifier_pattern(ayla::ast::IdentifierPatternNode *pattern) {

  if (current_scope->symbols.contains(pattern->name->str)) {

    // unit.diagnostics.create(DiagnosticCode::RedeclaredIdentifier, pattern->slice);
  
  }

  SymbolId sybol_id = unit.context.symbols.create_symbol(pattern->name->str, SymbolKind::Variable, Visibility::Private, false);
  auto symbol = unit.context.symbols.get(sybol_id);

  current_scope->symbols.insert(pattern->name->str, sybol_id);

  if (pattern->type_annotation) resolve_type_node(pattern->type_annotation);
}

void Resolver::resolve_pattern(ayla::ast::PatternNode *pat) {
  switch (pat->kind) {
  case ayla::ast::NodeKind::IdentifierPattern: resolve_identifier_pattern(static_cast<ayla::ast::IdentifierPatternNode *>(pat)); break;

  default: break;
  }
}
