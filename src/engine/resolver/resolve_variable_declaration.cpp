#include "Resolver.hpp"
#include "core/memory/symbol.hpp"

void Resolver::resolve_variable_declaration(core::ast::PatternNode *node) {

  if (!node || !node->identifier) return;

  if (current_scope->has_symbol_local(node->identifier->name)) {
    report_error(DiagnosticCode::RedeclaredIdentifier, node->identifier->slice, {{"name", node->identifier->name}});
    return;
  }

  auto symbol = unit.symbols.create_symbol(node->identifier->name, SymbolKind::Variable, Visibility::Public, false, node);

  current_scope->declare(node->identifier->name, symbol);
  node->symbol_id = symbol;

  if (node->type) resolve(node->type);
  if (node->value) resolve(node->value);

  Type *finalType = nullptr;

  if (node->type) {
    // finalType = node->type->resolved_type;
  } else if (node->value) {
    finalType = node->value->inferred_type;
  }

  node->inferred_type = finalType;

  Symbol *sym = unit.symbols.get(symbol);
  if (sym) { sym->type = finalType; }
}
