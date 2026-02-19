#include "semantic/resolver/Resolver.hpp"
#include <iostream>

void Resolver::resolve_identifier_exp(ayla::ast::node::IdentifierExpressionNode *node) {
  if (!node) return;

  SymbolId id = current_scope->resolve_symbol(node->name);

  if (!id.is_valid()) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->slice);
    return;
  }

  node->resolved_symbol_id = id;
  node->local_slot = current_scope->resolve_slot(id).value_or(0);
}

void Resolver::resolve_assign_exp(ayla::ast::node::AssignmentExpressionNode *node) {
  if (!node) return;

  // Resolve a target (já tem slot se for variável local)
  if (node->target) resolve(node->target);

  auto symbol = unit.context.symbol_manager.get(node->target->resolved_symbol_id);
  if (!symbol) return;

  if (symbol->modifiers.has(ayla::ast::Modifier::Mut)) { std::cout << "aaaaaaaaaaaaaaaa, e mut"; }

  // Resolve o value — o slot é temporário se não for variável
  if (node->value) resolve(node->value);

  // Opcional: você poderia armazenar o slot de value em node->local_slot
  // caso queira usar diretamente no bytecode
  node->local_slot = node->target->local_slot; // o destino é onde o valor vai
}

void Resolver::resolve_index_exp(ayla::ast::node::IndexAccessExpressionNode *node) {

  resolve(node->base);
  resolve(node->index);

  node->local_slot = current_scope->allocate_temporary();
}

void Resolver::resolve_member_exp(ayla::ast::node::MemberAccessExpressionNode *node) {
  if (!node || !node->base || !node->field) return;

  resolve(node->base);

  if (!node->base->resolved_symbol_id.is_valid()) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->slice);
    return;
  }

  node->local_slot = current_scope->allocate_temporary();
}

void Resolver::resolve_call_exp(ayla::ast::node::CallExpressionNode *node) {
  if (!node) return;
  resolve(node->callee);
  for (auto *arg : node->arguments) resolve(arg);
  node->local_slot = current_scope->allocate_temporary();
}

void Resolver::resolve_binary_exp(ayla::ast::node::BinaryExpressionNode *node) {
  if (!node) return;
  resolve(node->lhs);
  resolve(node->rhs);
  node->local_slot = current_scope->allocate_temporary();
}

void Resolver::resolve_unary_exp(ayla::ast::node::UnaryExpressionNode *node) {
  if (!node) return;
  resolve(node->operand);
  node->local_slot = current_scope->allocate_temporary();
}