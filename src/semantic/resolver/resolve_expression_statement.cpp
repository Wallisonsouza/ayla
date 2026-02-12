#include "semantic/resolver/Resolver.hpp"

void Resolver::resolve_expression_statement(ayla::ast::node::ExpressionStatementNode *node) {

  if (node->expression) { resolve(node->expression); }
}
