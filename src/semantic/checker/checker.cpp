#include "ayla/semantic/checker/checker.hpp"

namespace ayla {
void ayla::semantic::Checker::check(ast::AstNode *node) {
  if (!node) return;

  switch (node->kind) {
  case ast::NodeKind::ExpressionStatement:
    check_expression_statement(static_cast<ast::node::ExpressionStatementNode *>(node));
    break;
  case ast::NodeKind::IdentifierExpression:
    check_id_expression(static_cast<ast::node::IdentifierExpressionNode *>(node));
    break;
  case ast::NodeKind::NumberLiteral:
    check_number_literal(static_cast<ast::node::NumberLiteralNode *>(node));
    break;
  case ast::NodeKind::StringLiteral:
    check_string_literal(static_cast<ast::node::StringLiteralNode *>(node));
    break;
  case ast::NodeKind::BooleanLiteral:
    check_boolean_literal(static_cast<ast::node::BoolLiteralNode *>(node));
    break;
  case ast::NodeKind::ArrayLiteral:
    check_array_literal(static_cast<ast::node::ArrayLiteralNode *>(node));
    break;
  case ast::NodeKind::ObjectLiteral:
    check_object_literal(static_cast<ast::node::ObjectLiteralNode *>(node));
    break;
  case ast::NodeKind::VariableDeclaration:
    check_variable_declaration(static_cast<ast::node::VariableDeclarationNode *>(node));
    break;
  case ast::NodeKind::FunctionDeclaration:
    check_function_declaration(static_cast<ast::node::FunctionDeclarationNode *>(node));
    break;
  case ast::NodeKind::CallExpression:
    check_call_expression(static_cast<ast::node::CallExpressionNode *>(node));
    break;
  case ast::NodeKind::BinaryExpression:
    check_binary_expression(static_cast<ast::node::BinaryExpressionNode *>(node));
    break;
  case ast::NodeKind::MemberAccessExpression:
    check_member_expression(static_cast<ast::node::MemberAccessExpressionNode *>(node));
    break;
  case ast::NodeKind::IndexAccessExpression:
    check_index_expression(static_cast<ast::node::IndexAccessExpressionNode *>(node));
    break;
  case ast::NodeKind::AssignmentExpression:
    check_assign_expression(dynamic_cast<ast::node::AssignmentExpressionNode *>(node));
    break;
  case ast::NodeKind::IfStatement:
    check_if_statement(static_cast<ast::node::IfStatementNode *>(node));
    break;
  case ast::NodeKind::WhileStatement:
    check_while_statement(static_cast<ast::node::WhileStatementNode *>(node));
    break;
  case ast::NodeKind::ReturnStatement:
    check_return_statement(static_cast<ast::node::ReturnStatementNode *>(node));
    break;
  case ast::NodeKind::BlockStatement:
    check_block_statement(static_cast<ast::node::BlockStatementNode *>(node));
    break;
  case ast::NodeKind::ImportStatement:
    check_import_statement(static_cast<ast::node::ImportStatementNode *>(node));
    break;
  case ast::NodeKind::ModuleDeclaration:
    check_module_declaration(static_cast<ast::node::ModuleDeclarationNode *>(node));
    break;
  case ast::NodeKind::Pattern:
    check_pattern(static_cast<ast::PatternNode *>(node));
    break;
  case ast::NodeKind::UnaryExpression:
    check_unary_expression(static_cast<ast::node::UnaryExpressionNode *>(node));
    break;
  default:
    break;
  }
}

} // namespace ayla
