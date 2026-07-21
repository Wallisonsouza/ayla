#include "AstDumper.hpp"

void AstDumper::debug_while_statement(const ayla::ast::node::WhileStatementNode *node) {

  out << "While\n";

  if (node->condition) { debug_node(node->condition, false); }

  if (node->body) { debug_node(node->body, true); }
}

void AstDumper::debug_block_statement(const ayla::ast::node::BlockStatementNode *node) {

  debug_header("BlockExpression");

  bool has_statements = !node->statements.empty();

  if (has_statements) { debug_labeled_childrens(node->statements, "Statements: ", true); }
}

void AstDumper::debug_if_statement(const ayla::ast::node::IfStatementNode *node) {

  debug_header("If");

  std::vector<LabeledChild> children;

  if (node->condition) children.push_back({"Condition: ", node->condition});

  if (node->then_block) children.push_back({"Then: ", node->then_block});

  if (node->else_block) children.push_back({"Else: ", node->else_block});

  for (size_t i = 0; i < children.size(); ++i) {
    bool is_last = (i + 1 == children.size());
    debug_labeled(children[i].label, children[i].node, is_last);
  }
}

void AstDumper::debug_return_statement(const ayla::ast::node::ReturnStatementNode *node) {

  debug_header("ReturnStatement");

  debug_labeled("Value", node->value, true);
}

void AstDumper::debug_expression_statement(const ayla::ast::node::ExpressionStatementNode *node) {

  out << "ExpressionStatement\n";

  debug_node(node->expression, true);
}

void AstDumper::debug_import_statement(const ayla::ast::node::ImportStatementNode *node) {
  out << "Import\n";

  size_t count = node->name->parts.size();

  for (size_t i = 0; i < count; ++i) { debug_node(node->name->parts[i], i == count - 1); }
}
