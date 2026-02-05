#include "ast_debug.hpp"

void ASTDebug::debug_block(const ayla::ast::node::BlockStatementNode *node) {

  debug_header("BlockExpression");

  bool has_statements = !node->statements.empty();

  if (has_statements) { debug_labeled_childrens(node->statements, "Statements", true); }
}
