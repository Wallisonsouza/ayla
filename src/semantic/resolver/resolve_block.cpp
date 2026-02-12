
#include "semantic/resolver/Resolver.hpp"

void Resolver::resolve_block(ayla::ast::node::BlockStatementNode *node, bool create_scope) {

  if (create_scope) push_scope();

  for (auto *stmt : node->statements) { resolve(stmt); }

  if (create_scope) pop_scope();
}

void Resolver::resolve_return_statement(ayla::ast::node::ReturnStatementNode *node) {
  if (node->value) { resolve(node->value); }
}