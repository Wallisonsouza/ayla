#include "ast_debug.hpp"
#include "core/node/BinaryOp.hpp"

void ASTDebug::debug_binary_expression(const ayla::ast::node::BinaryExpressionNode *node) {

  debug_header("BinaryExpression: " + ayla::ast::binary_op_to_string(node->op));

  if (node->lhs) { debug_labeled("Left", node->lhs, false); }

  if (node->rhs) { debug_labeled("Right", node->rhs, true); }
}

void ASTDebug::debug_unary_expression(const ayla::ast::node::UnaryExpressionNode *node) {

  debug_header("UnaryExpression: ");

  if (node->operand) { debug_labeled("Operand", node->operand, true); }
}
