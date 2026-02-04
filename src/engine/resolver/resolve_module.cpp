#include "Resolver.hpp"

void Resolver::resolve_module_declaration(parser::node::statement::ModuleDeclarationNode *node) {
  if (!node || node->path.empty()) return;

  ModuleId module_id = unit.context.module_manager.create_module_path(node->path);
  auto module = unit.context.module_manager.get(module_id);
  node->resolved_module_id = module_id;

  std::string module_name = node->path.back()->name;

  auto *prev_scope = current_scope;
  enter_scope(&module->parser_scope);

  for (auto *stmt : node->body) resolve(stmt);

  leave_scope(prev_scope);
}

void Resolver::resolve_import_node(parser::node::statement::ImportNode *node) {
  if (!node || node->path.empty()) return;

  size_t failed_index;
  ModuleId module_id = unit.context.module_manager.find_path(node->path, failed_index);

  if (module_id == INVALID_MODULE) {
    report_error(DiagnosticCode::ModuleNotFound, node->slice, {{"name", node->path[failed_index]->name}});
    return;
  }

  auto module = unit.context.module_manager.get(module_id);

  std::string local_name = node->alias.value_or(node->path.back()->name);

  // Registrar no escopo atual, não dentro do próprio módulo
  if (current_scope->has_symbol_local(local_name)) {
    report_error(DiagnosticCode::RedeclaredIdentifier, node->slice, {{"name", local_name}});
    return;
  }

  SymbolId sym_id = unit.symbols.create_symbol(local_name, SymbolKind::Module, Visibility::Public, true, node);
  unit.symbols.get(sym_id)->module_id = module_id;
  current_scope->declare(local_name, sym_id);

  node->resolved_symbol_id = sym_id;
}
