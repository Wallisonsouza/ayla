#include "ast_debug.hpp"
#include "frontend/ast/expressions/AssignmentExpression.hpp"

void ASTDebug::debug_ASSIGN_node(const ayla::ast::node::AssignmentExpressionNode *node) {
  out << "ASSIGN\n";

  if (node->target) { debug_labeled("Target", node->target, false); }

  if (node->value) { debug_labeled("Value", node->value, true); }
}