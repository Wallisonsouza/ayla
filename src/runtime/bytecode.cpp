#include "runtime/ByteCode.hpp"

namespace ayla::compiler {
uint8_t BytecodeGenerator::gen_expressions(ayla::ast::AstNode *node, uint8_t dst) {
  switch (node->kind) {

  case ast::NodeKind::NumberLiteral:
    return gen_number_literal(static_cast<ast::node::NumberLiteralNode *>(node), dst);

  case ast::NodeKind::StringLiteral:
    return gen_string_literal(static_cast<ast::node::StringLiteralNode *>(node), dst);

  case ast::NodeKind::BooleanLiteral:
    return gen_boolean_literal(static_cast<ast::node::BoolLiteralNode *>(node), dst);

  case ast::NodeKind::ArrayLiteral:
    return gen_array_literal(static_cast<ast::node::ArrayLiteralNode *>(node), dst);

  case ast::NodeKind::ObjectLiteral:
    return gen_object_literal(static_cast<ast::node::ObjectLiteralNode *>(node), dst);

  case ast::NodeKind::IdentifierExpression:
    return gen_identifier_expression(static_cast<ast::node::IdentifierExpressionNode *>(node), dst);

  case ast::NodeKind::BinaryExpression:
    return gen_binary_expression(static_cast<ast::node::BinaryExpressionNode *>(node), dst);

  case ast::NodeKind::MemberAccessExpression:
    return gen_member_expression(static_cast<ast::node::MemberAccessExpressionNode *>(node), dst);

  case ast::NodeKind::IndexAccessExpression:
    return gen_index_expression(static_cast<ast::node::IndexAccessExpressionNode *>(node), dst);

    // case ast::NodeKind::AssignmentExpression:
    //   return gen_assignment_expression(static_cast<ast::node::AssignmentExpressionNode *>(node), dst);

  default:
    throw std::runtime_error("Unhandled expression node");
  }
}

void BytecodeGenerator::gen_statements(ayla::ast::AstNode *node) {

  switch (node->kind) {
  case ast::NodeKind::VariableDeclaration:
    gen_variable_declaration(static_cast<ast::node::VariableDeclarationNode *>(node));
    break;
  case ast::NodeKind::AssignmentExpression:
    gen_assignment_expression(static_cast<ast::node::AssignmentExpressionNode *>(node));
    break;
  case ast::NodeKind::ExpressionStatement:
    gen_expression_statement(static_cast<ast::node::ExpressionStatementNode *>(node));
    break;
  case ast::NodeKind::ReturnStatement:
    gen_return_statement(static_cast<ast::node::ReturnStatementNode *>(node));
    break;
  case ast::NodeKind::BlockStatement:
    gen_block_statement(static_cast<ast::node::BlockStatementNode *>(node));
    break;
  case ast::NodeKind::FunctionDeclaration:
    gen_function_declaration(static_cast<ast::node::FunctionDeclarationNode *>(node));
    break;
  case ast::NodeKind::ModuleDeclaration:
    gen_module_declaration(static_cast<ast::node::ModuleDeclarationNode *>(node));
    break;
  case ast::NodeKind::ImportStatement:
    gen_import_statement(static_cast<ast::node::ImportStatementNode *>(node));
    break;
  default:
    break;
  }
}

} // namespace ayla::compiler