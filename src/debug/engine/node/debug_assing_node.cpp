#include "ast_debug.hpp"

void ASTDebug::debug_ASSIGN_node(const parser::node::statement::AssignmentNode *node) {
  out << "ASSIGN\n";

  if (node->target) { debug_labeled("Target", node->target, false); }

  if (node->value) { debug_labeled("Value", node->value, true); }
}