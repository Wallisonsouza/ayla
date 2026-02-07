#include "ast_debug.hpp"

void ASTDebug::debug_path_expression(const ayla::ast::node::MemberAccessExpressionNode *node) {

  debug_header("MemberAccessNode");

  debug_labeled("Base", node->base, false);
  debug_labeled("Field", node->field, true);
}