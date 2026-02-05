#include "engine/parser/node/statement_nodes.hpp"
#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_if_statement(ayla::ast::node::IfStatementNode *node) {
  if (!node) return;

  if (node->condition) { resolve(node->condition); }

  if (node->then_block) { resolve(node->then_block); }

  if (node->else_block) { resolve(node->else_block); }
}

void Resolver::resolve_while_statement(parser::node::ASTWhileStatementNode *node) {
  if (!node) return;

  if (node->condition) { resolve(node->condition); }

  if (node->body) { resolve(node->body); }
}
