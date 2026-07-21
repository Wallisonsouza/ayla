#include "AstDumper.hpp"


void AstDumper::debug_call_expression(const ayla::ast::node::CallExpressionNode *node) {
  out << "FunctionCall\n";

  if (node->callee) {
    bool callee_is_last = node->arguments.empty();
    debug_labeled("Callee", node->callee, callee_is_last);
  }

  if (!node->arguments.empty()) { debug_labeled_childrens(node->arguments, "Args", true); }
}

void AstDumper::debug_binary_expression(const ayla::ast::node::BinaryExpressionNode *node) {

debug_header(std::format("BinaryExpression(\"{}\")", to_string(node->op)));

  if (node->lhs) { debug_labeled("Left: ", node->lhs, false); }

  if (node->rhs) { debug_labeled("Right: ", node->rhs, true); }
}

void AstDumper::debug_unary_expression(const ayla::ast::node::UnaryExpressionNode *node) {

  debug_header("UnaryExpression: ");

  if (node->operand) { debug_labeled("Operand", node->operand, true); }
}

void AstDumper::debug_assignment_expression(const ayla::ast::node::AssignmentExpressionNode *node) {
  out << "ASSIGN\n";

  if (node->target) { debug_labeled("Target", node->target, false); }

  if (node->value) { debug_labeled("Value", node->value, true); }
}

void AstDumper::debug_index_acess_expression(const ayla::ast::node::IndexAccessExpressionNode *node) {

  debug_header("IndexAcess");

  debug_labeled("Base", node->base, false);
  debug_labeled("Index", node->index, true);
}

void AstDumper::debug_identifier_expression(const ayla::ast::node::IdentifierExpressionNode *node) {

  if (node->name) { debug_header(std::format("IdentifierExpression(\"{}\")", node->name->str)); }
}

void AstDumper::debug_member_acess_expression(const ayla::ast::node::MemberAccessExpressionNode *node) {

  debug_header("MemberAccessNode");

  debug_labeled("Base", node->base, false);
  debug_labeled("Field", node->member, true);
}