#include "celestia/debug/ast/AstDumper.hpp"

void AstDumper::dump_while_statement(const celestia::ast::node::WhileStatementNode *node) {

  auto g = context.object("WhileStatement");

  g.field("Condition", node->condition);
  g.field("Body", node->body);
}

void AstDumper::dump_block_statement(const celestia::ast::node::BlockStatementNode *node) {

  auto g = context.object("BlockStatement");

  g.list("Statements", node->statements);
}

void AstDumper::dump_if_statement(const celestia::ast::node::IfStatementNode *node) {

  auto g = context.object("IfStatement");

  g.field("Condition", node->condition);
  g.field("Then", node->then_block);
  g.field("Else", node->else_block);
}

void AstDumper::dump_return_statement(const celestia::ast::node::ReturnStatementNode *node) {

  auto g = context.object("ReturnStatement");

  g.field("Value", node->value);
}

void AstDumper::dump_expression_statement(const celestia::ast::node::ExpressionStatementNode *node) {

  auto g = context.object("ExpressionStatement");

  g.field("Expression", node->expression);
}

void AstDumper::dump_import_statement(const celestia::ast::node::ImportDeclarationNode *node) {

  auto g = context.object("ImportStatement");

  if (node->name) g.list("Path", node->name->parts);
}