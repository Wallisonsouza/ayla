#include "Resolver.hpp"
#include "celestia/ast/NodeKind.hpp"


void Resolver::identifier_pattern(celestia::ast::IdentifierPatternNode *pattern) {

  if (context.scopes.current()->symbols.contains(pattern->name->str)) {

    // unit.diagnostics.create(DiagnosticCode::RedeclaredIdentifier, pattern->slice);
  
  }

  SymbolId sybol_id = context.compiler.symbols.create_symbol(pattern->name->str, SymbolKind::Variable, Visibility::Private, false);
  auto symbol = context.compiler.symbols.get(sybol_id);

  context.scopes.current()->symbols.insert(pattern->name->str, sybol_id);

  if (pattern->type_annotation) type_node(pattern->type_annotation);
}

void Resolver::pattern(celestia::ast::PatternNode *pat) {
  switch (pat->kind) {
  case celestia::ast::NodeKind::IdentifierPattern: identifier_pattern(static_cast<celestia::ast::IdentifierPatternNode *>(pat)); break;

  default: break;
  }
}
