#include "Resolver.hpp"

void Resolver::resolve_function_declaration(ayla::ast::node::FunctionDeclarationNode *node) {
  if (!node) return;

  if (current_scope->has_symbol_local(node->identifier->name)) {
    report_error(DiagnosticCode::RedeclaredIdentifier, node->identifier->slice, {{"name", node->identifier->name}});
    return;
  }

  SymbolId sym_id = unit.context.symbol_manager.create_symbol(node->identifier->name, SymbolKind::Function, Visibility::Public, false, node);

  current_scope->declare(node->identifier->name, sym_id);
  node->symbol_id = sym_id;

  if (node->modifiers.has(ayla::ast::Modifier::Extern)) return;

  push_scope();

  for (auto *param : node->params) {
    SymbolId pid = unit.context.symbol_manager.create_symbol(param->identifier->name, SymbolKind::Variable, Visibility::Private, false, param);
    current_scope->declare(param->identifier->name, pid);
    param->symbol_id = pid;
  }

  if (node->body) resolve_block(node->body, false);

  pop_scope();
}
