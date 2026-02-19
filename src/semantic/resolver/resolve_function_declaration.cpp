#include "Resolver.hpp"

void Resolver::resolve_function_declaration(ayla::ast::node::FunctionDeclarationNode *node) {

  if (!node) return;

  // --- Bind da função ---
  if (current_scope->has_symbol_local(node->identifier->name)) {
    report_error(DiagnosticCode::RedeclaredIdentifier, node->identifier->slice, {{"name", node->identifier->name}});
    return;
  }

  SymbolId sym_id = unit.context.symbol_manager.create_symbol(node->identifier->name, SymbolKind::Function, Visibility::Public, false, node);

  current_scope->declare(node->identifier->name, sym_id);
  node->symbol_id = sym_id;
  node->local_slot = current_scope->resolve_slot(sym_id).value_or(0);

  if (node->modifiers.has(ayla::ast::Modifier::Extern)) return;

  // --- Escopo da função ---
  push_scope();

  // --- Bind dos parâmetros (AGORA PATTERNS) ---
  for (auto *param : node->parameters) { resolve_pattern(param, node->modifiers); }

  if (node->body) resolve_block(node->body, false);

  pop_scope();
}
