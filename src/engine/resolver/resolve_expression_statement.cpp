#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_expression_statement(core::ast::ExpressionStatementNode *node) {

  if (node->expression) { resolve(node->expression); }
}
