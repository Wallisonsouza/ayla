#include "ast_debug.hpp"

void ASTDebug::debug_return_statement(const ayla::ast::node::ReturnStatementNode *node) {

  debug_header("ReturnStatement");

  debug_labeled("Value", node->value, true);
}
