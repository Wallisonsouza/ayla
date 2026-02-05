#include "ast_debug.hpp"
#include "core/node/Type.hpp"

void ASTDebug::debug_expression_statement(const ayla::ast::ExpressionStatementNode *node) {

  out << "ExpressionStatement\n";

  debug_node(node->expression, true);
}
