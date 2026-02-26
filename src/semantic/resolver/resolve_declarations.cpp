#include "semantic/resolver/Resolver.hpp"

void Resolver::resolve_module_declaration(ayla::ast::node::ModuleDeclarationNode *node) {
  if (!node || node->path.empty()) return;

  ModuleId module_id = unit.context.module_manager.get_or_create_module_path(node->path);
  auto module = unit.context.module_manager.get(module_id);
  node->resolved_module_id = module_id;

  std::string module_name = node->path.back()->name;

  module->parser_scope = unit.scope_manager.create_scope(nullptr);

  auto *prev = current_scope;
  current_scope = module->parser_scope;

  for (auto *stmt : node->body) resolve(stmt);

  current_scope = prev;
}

void Resolver::resolve_variable_declaration(ayla::ast::node::VariableDeclarationNode *node) {
  if (!node) return;

  if (node->pattern) { resolve_pattern(node->pattern, node->modifiers); }

  node->local_slot = node->pattern->local_slot;

  if (node->initializer) { resolve(node->initializer); }
}

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

  // --- Bind dos parâmetros ---
  for (auto *param : node->parameters) { resolve_pattern(param, node->modifiers); }

  if (node->body) resolve_block_statement(node->body, false);

  pop_scope();
}