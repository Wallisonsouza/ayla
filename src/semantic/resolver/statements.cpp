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

  node->local_slot = current_scope->resolve_slot(sym_id).value_or(current_scope->allocate_temporary());

  if (node->modifiers.has(ayla::ast::Modifier::Extern)) return;

  // --- Escopo da função ---
  push_scope();

  // --- Bind dos parâmetros ---
  for (auto *param : node->parameters) { resolve_pattern(param, node->modifiers); }

  if (node->body) resolve_block_statement(node->body, false);

  pop_scope();
}

void Resolver::resolve_variable_declaration(ayla::ast::node::VariableDeclarationNode *node) {
  if (!node) return;

  if (node->pattern) { resolve_pattern(node->pattern, node->modifiers); }

  node->local_slot = node->pattern->local_slot;

  if (node->initializer) { resolve(node->initializer); }
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