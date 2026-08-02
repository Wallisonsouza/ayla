
#include "celestia/ast/expressions/AssignmentExpression.hpp"
#include "celestia/ast/expressions/BinaryExpressionNode.hpp"
#include "celestia/ast/expressions/CallExpressionNode.hpp"
#include "celestia/ast/expressions/IdentifierExpressionNode.hpp"
#include "celestia/ast/expressions/IndexAcessExpressionNode.hpp"
#include "celestia/ast/expressions/MemberAccessExpressionNode.hpp"
#include "celestia/ast/expressions/UnaryExpressionNode.hpp"
#include "celestia/debug/ast/AstDumper.hpp"
#include <format>

namespace celestia::debug {
void AstDumper::dump_call_expression(const ast::CallExpressionNode *node) {
  auto g = context.object("FunctionCall");

  g.field("Callee", node->callee);
  g.list("Arguments", node->arguments);
}

void AstDumper::dump_binary_expression(const ast::BinaryExpressionNode *node) {
  auto g = context.object(std::format("BinaryExpression(\"{}\")", to_string(node->op)));

  g.field("Left", node->lhs);
  g.field("Right", node->rhs);
}

void AstDumper::dump_unary_expression(const ast::UnaryExpressionNode *node) {
  auto g = context.object("UnaryExpression");

  g.field("Operand", node->operand);
}

void AstDumper::dump_assignment_expression(const ast::AssignmentExpressionNode *node) {
  auto g = context.object("Assignment");

  g.field("Target", node->target);
  g.field("Value", node->value);
}

void AstDumper::dump_index_acess_expression(const ast::IndexAccessExpressionNode *node) {
  auto g = context.object("IndexAccess");

  g.field("Base", node->base);
  g.field("Index", node->index);
}

void AstDumper::dump_identifier_expression(const ast::IdentifierExpressionNode *node) {
  if (node->name) {
    auto g = context.object(std::format("IdentifierExpression(\"{}\")", node->name->str));

    (void)g;
  } else {
    auto g = context.object("IdentifierExpression");

    (void)g;
  }
}

void AstDumper::dump_member_acess_expression(const ast::MemberAccessExpressionNode *node) {
  auto g = context.object("MemberAccess");

  g.field("Base", node->base);
  g.field("Field", node->member);
}
} // namespace celestia::debug