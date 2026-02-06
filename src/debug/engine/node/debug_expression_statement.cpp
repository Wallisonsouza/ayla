#include "ast_debug.hpp"

void ASTDebug::debug_expression_statement(const ayla::ast::node::ExpressionStatementNode *node) {

  out << "ExpressionStatement\n";

  debug_node(node->expression, true);
}
