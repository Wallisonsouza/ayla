#include "semantic/resolver/Resolver.hpp"

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

void Resolver::resolve_expression_statement(ayla::ast::node::ExpressionStatementNode *node) {

  if (node->expression) { resolve(node->expression); }
}

void Resolver::resolve_block(ayla::ast::node::BlockStatementNode *node, bool create_scope) {

  auto *scope = unit.scopes.create_scope(current_scope);

  if (create_scope) push_scope(*scope);

  for (auto *stmt : node->statements) { resolve(stmt); }

  if (create_scope) pop_scope();
}

void Resolver::resolve_return_statement(ayla::ast::node::ReturnStatementNode *node) {
  if (node->value) { resolve(node->value); }
}