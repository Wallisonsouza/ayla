#include "ayla-semantic/ayla-resolver/Resolver.hpp"
#include "ayla-structural/ayla-ast/statement_nodes.hpp"

void Resolver::resolve_if_statement(parser::node::IfStatementNode *node) {
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
