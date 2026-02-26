#include "semantic/resolver/Resolver.hpp"

void Resolver::resolve_block_statement(ayla::ast::node::BlockStatementNode *node, bool create_scope) {
  if (!node) return;

  if (create_scope) push_scope();

  for (auto *stmt : node->statements) { resolve(stmt); }

  if (create_scope) pop_scope();
}

void Resolver::resolve_return_statement(ayla::ast::node::ReturnStatementNode *node) {
  if (!node) return;

  if (node->value) {
    resolve(node->value);
    // node->local_slot = allocate_temporary();
  }
}

void Resolver::resolve_expression_statement(ayla::ast::node::ExpressionStatementNode *node) {

  if (node->expression) { resolve(node->expression); }
}

void Resolver::resolve_if_statement(ayla::ast::node::IfStatementNode *node) {
  if (!node) return;

  if (node->condition) { resolve(node->condition); }

  if (node->then_block) { resolve(node->then_block); }

  if (node->else_block) { resolve(node->else_block); }
}

void Resolver::resolve_while_statement(ayla::ast::node::WhileStatementNode *node) {
  if (!node) return;

  if (node->condition) { resolve(node->condition); }

  if (node->body) { resolve(node->body); }
}

void Resolver::resolve_import_statement(ayla::ast::node::ImportStatementNode *node) {
  if (!node || node->path.empty()) return;

  size_t failed_index;
  ModuleId module_id = unit.context.module_manager.find_path(node->path, failed_index);

  if (module_id == INVALID_MODULE) {
    report_error(DiagnosticCode::ModuleNotFound, node->slice, {{"name", node->path[failed_index]->name}});
    return;
  }

  node->resolved_module_id = module_id;

  auto module = unit.context.module_manager.get(module_id);

  std::string local_name = node->alias.value_or(node->path.back()->name);

  if (current_scope->has_symbol_local(local_name)) {
    report_error(DiagnosticCode::RedeclaredIdentifier, node->slice, {{"name", local_name}});
    return;
  }

  SymbolId sym_id = unit.context.symbol_manager.create_symbol(local_name, SymbolKind::Module, Visibility::Public, true, node);

  unit.context.symbol_manager.get(sym_id)->module_id = module_id;

  current_scope->declare(local_name, sym_id);

  node->resolved_symbol_id = sym_id;
}
