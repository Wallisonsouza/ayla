#include "Resolver.hpp"

#include "Resolver.hpp"
#include "core/memory/symbol.hpp"

void Resolver::resolve_module_declaration(parser::node::statement::ModuleDeclarationNode *node) {
  if (!node || node->path.empty()) return;

  // 1) Registrar módulo no ModuleManager
  auto module_id = unit.context.module_manager.create_module_path(node->path);
  node->resolved_module_id = module_id;

  // 2) Criar escopo temporário do módulo para resolver seu corpo
  push_scope();
  for (auto &stmt : node->body) { resolve(stmt); }
  pop_scope();

  // Opcional: registrar type ou outros dados do módulo
  // auto *module_type = unit.type_arena.alloc<ModuleType>();
  // unit.context.module_manager.register_module(node->path, module_id, module_type);
}

void Resolver::resolve_import_node(parser::node::statement::ImportNode *node) {
  if (!node || node->path.empty()) return;

  // 1) Buscar módulo no ModuleManager
  size_t failed_index;
  auto module_id = unit.context.module_manager.find_path(node->path, failed_index);
  if (module_id == INVALID_MODULE) {
    report_error(DiagnosticCode::ModuleNotFound, node->slice, {{"name", node->path[failed_index]->name}});
    return;
  }
  node->resolved_module_id = module_id;

  // 2) Determinar nome local no escopo
  std::string local_name = node->alias.value_or(node->path.back()->name);

  // 3) Evitar redeclaração no escopo atual
  if (current_scope->has_symbol_local(local_name)) {
    report_error(DiagnosticCode::RedeclaredIdentifier, node->slice, {{"name", local_name}});
    return;
  }

  SymbolId sym_id = unit.symbols.create_symbol(local_name, SymbolKind::Module, Visibility::Public, true, node);

  unit.symbols.get(sym_id)->module_id = module_id;

  current_scope->declare(local_name, sym_id);

  node->resolved_symbol_id = sym_id;
}
