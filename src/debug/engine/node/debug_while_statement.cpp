#include "ast_debug.hpp"

void ASTDebug::debug_while(const ayla::ast::node::WhileStatementNode *node) {

  out << "While\n";

  if (node->condition) { debug_node(node->condition, false); }

  if (node->body) { debug_node(node->body, true); }
}