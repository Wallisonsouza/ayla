#include "ast_debug.hpp"
#include "ayla-structural/ayla-ast/statement_nodes.hpp"

void ASTDebug::debug_while(const parser::node::ASTWhileStatementNode *node) {

  out << "While\n";

  if (node->condition) { debug_node(node->condition, false); }

  if (node->body) { debug_node(node->body, true); }
}