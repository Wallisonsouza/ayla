#include "Resolver.hpp"
#include "ast/declarations/ModuleDeclarationNode.hpp"
#include "module/Module.hpp"
#include <iostream>

void Resolver::resolve_module_declaration(ayla::ast::node::ModuleDeclarationNode *node) {

  auto mod = unit.context.modules.register_module(node->name->get_name());

  if (!mod) return;

  push_scope(mod->get_scope());

  for (auto &declaration : node->declarations) resolve(declaration);

  pop_scope();
}

void Resolver::resolve_import_declaration(ayla::ast::node::ImportDeclarationNode *node) {
  // if (!node || node->path.empty()) return;

  // size_t failed_index;
  // ModuleId module_id = unit.context.module_manager.find_path(node->path, failed_index);

  // if (module_id == INVALID_MODULE) {
  //   //report_error(DiagnosticCode::ModuleNotFound, node->slice, {{"name", node->path[failed_index]->name}});
  //   return;
  // }

  // node->resolved_module_id = module_id;

  // auto module = unit.context.module_manager.get(module_id);

  // std::string local_name = node->alias.value_or(node->path.back()->name);

  // if (current_scope->has_symbol_local(local_name)) {
  //   //report_error(DiagnosticCode::RedeclaredIdentifier, node->slice, {{"name", local_name}});
  //   return;
  // }

  // SymbolId sym_id = unit.context.symbol_manager.create_symbol(local_name, SymbolKind::Module, Visibility::Public, true, node);

  // unit.context.symbol_manager.get(sym_id)->module_id = module_id;

  // current_scope->declare(local_name, sym_id);

  // node->resolved_symbol_id = sym_id;
}

void Resolver::resolve_function_declaration(ayla::ast::node::FunctionDeclarationNode *node) {

  if (!node) return;

  // --- Bind da função ---
  if (current_scope->has_symbol_local(node->name->str)) {

    std::cout << "erro redefiicao";
    // report_error(DiagnosticCode::RedeclaredIdentifier, node->identifier->slice, {{"name", node->identifier->name}});
    return;
  }

  SymbolId sym_id = unit.context.symbols.create_symbol(node->name->str, SymbolKind::Function, Visibility::Public, false, node);

  current_scope->symbols.insert(node->name->str, sym_id);
  node->symbol_id = sym_id;

  if (node->specifiers.modifiers.has(Modifier::Extern)) return;

  auto *fun_scope = unit.scopes.create_scope(current_scope);

  push_scope(*fun_scope);

  for (auto *param : node->parameters) { resolve_pattern(param); }

  if (node->body) resolve_block(node->body, false);

  pop_scope();
}

void Resolver::resolve_variable_declaration(ayla::ast::node::VariableDeclarationNode *node) {

  if (node->pattern) { resolve_pattern(node->pattern); }

  if (node->initializer) { resolve(node->initializer); }
}
