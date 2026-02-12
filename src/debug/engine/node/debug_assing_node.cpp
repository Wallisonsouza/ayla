#include "ast/expressions/AssignmentExpression.hpp"
#include "ast_debug.hpp"

void ASTDebug::debug_ASSIGN_node(const ayla::ast::node::AssignmentExpressionNode *node) {
  out << "ASSIGN\n";

  if (node->target) { debug_labeled("Target", node->target, false); }

  if (node->value) { debug_labeled("Value", node->value, true); }
}