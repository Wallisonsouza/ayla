#include "Resolver.hpp"
#include "celestia/ast/declarations/ModuleDeclarationNode.hpp"
#include <iostream>

void Resolver::module_declaration(celestia::ast::ModuleDeclaration *node) {

  auto mod = context.compiler.modules.register_module(node->name->get_name());

  if (!mod) return;

  context.scopes.push(mod->get_scope());

  for (auto &declaration : node->declarations) resolve(declaration);

  context.scopes.pop();
}

void Resolver::import_declaration(celestia::ast::ImportDeclarationNode *node) {
  // if (!node || node->path.empty()) return;

  // size_t failed_index;
  // ModuleId module_id = context.unit.context.module_manager.find_path(node->path, failed_index);

  // if (module_id == INVALID_MODULE) {
  //   //report_error(DiagnosticCode::ModuleNotFound, node->slice, {{"name", node->path[failed_index]->name}});
  //   return;
  // }

  // node->resolved_module_id = module_id;

  // auto module = context.unit.context.module_manager.get(module_id);

  // std::string local_name = node->alias.value_or(node->path.back()->name);

  // if (context.scopes.current()->has_symbol_local(local_name)) {
  //   //report_error(DiagnosticCode::RedeclaredIdentifier, node->slice, {{"name", local_name}});
  //   return;
  // }

  // SymbolId sym_id = context.unit.context.symbol_manager.create_symbol(local_name, SymbolKind::Module, Visibility::Public, true, node);

  // context.unit.context.symbol_manager.get(sym_id)->module_id = module_id;

  // context.scopes.current()->declare(local_name, sym_id);

  // node->resolved_symbol_id = sym_id;
}

void Resolver::function_declaration(celestia::ast::FunctionDeclarationNode *node) {

  if (!node) return;

  // --- Bind da função ---
  if (context.scopes.current()->has_symbol_local(node->name->str)) {

    std::cout << "erro redefiicao";
    // report_error(DiagnosticCode::RedeclaredIdentifier, node->identifier->slice, {{"name", node->identifier->name}});
    return;
  }

  SymbolId sym_id = context.compiler.symbols.create_symbol(node->name->str, SymbolKind::Function, Visibility::Public, false, node);

  context.scopes.current()->symbols.insert(node->name->str, sym_id);
  node->symbol_id = sym_id;

  if (node->specifiers.modifiers.has(Modifier::Extern)) return;

  auto *fun_scope = context.unit.scopes.create_scope(context.scopes.current());



  context.scopes.push(*fun_scope);

  for (auto *param : node->parameters) { pattern(param); }

  if (node->body) block(node->body);

  context.scopes.pop();
}

void Resolver::variable_declaration(celestia::ast::VariableDeclarationNode *node) {

  if (node->pattern) { pattern(node->pattern); }

  if (node->initializer) { resolve(node->initializer); }
}
