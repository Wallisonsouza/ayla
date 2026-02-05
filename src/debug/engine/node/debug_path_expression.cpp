#include "ast_debug.hpp"

void ASTDebug::debug_path_expression(const ayla::ast::node::MemberAccessExpressionNode *node) {

  debug_header("MemberAccessNode");

  debug_labeled("Base", node->base, false);
  debug_labeled("Field", node->field, true);
  // size_t count = node->segments.size();
  // for (size_t i = 0; i < count; ++i) { debug_node(node->segments[i], i == count - 1); }
}
