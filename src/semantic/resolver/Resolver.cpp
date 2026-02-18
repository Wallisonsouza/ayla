#include "Resolver.hpp"
#include "ast/expressions/UnaryExpressionNode.hpp"
#include "core/node/flags.hpp"

void Resolver::resolve(ayla::ast::AstNode *node) {

  if (!node || node->flags.has(NodeFlags::Resolved)) return;

  node->flags.set(NodeFlags::Resolved);

  switch (node->kind) {

  case ayla::ast::NodeKind::NumberLiteral: resolve_number_literal(static_cast<ayla::ast::node::NumberLiteralNode *>(node)); break;

  case ayla::ast::NodeKind::StringLiteral: resolve_string_literal(static_cast<ayla::ast::node::StringLiteralNode *>(node)); break;

  case ayla::ast::NodeKind::BooleanLiteral: resolve_boolean_literal(static_cast<ayla::ast::node::BoolLiteralNode *>(node)); break;

  case ayla::ast::NodeKind::IfStatement: resolve_if_statement(static_cast<ayla::ast::node::IfStatementNode *>(node)); break;

  case ayla::ast::NodeKind::WhileStatement: resolve_while_statement(static_cast<ayla::ast::node::WhileStatementNode *>(node)); break;

  case ayla::ast::NodeKind::BlockStatement: resolve_block(static_cast<ayla::ast::node::BlockStatementNode *>(node)); break;

  case ayla::ast::NodeKind::BinaryExpression: resolve_binary_expression(static_cast<ayla::ast::node::BinaryExpressionNode *>(node)); break;

  case ayla::ast::NodeKind::MemberAccessExpression: resolve_member_access(static_cast<ayla::ast::node::MemberAccessExpressionNode *>(node)); break;

  case ayla::ast::NodeKind::ImportStatement: resolve_import_node(static_cast<ayla::ast::node::ImportStatementNode *>(node)); break;

  case ayla::ast::NodeKind::Identifier: resolve_identifier(static_cast<ayla::ast::node::IdentifierExpressionNode *>(node)); break;

  case ayla::ast::NodeKind::CallExpression: resolve_function_call(static_cast<ayla::ast::node::CallExpressionNode *>(node)); break;

  case ayla::ast::NodeKind::ExpressionStatement: resolve_expression_statement(static_cast<ayla::ast::node::ExpressionStatementNode *>(node)); break;

  case ayla::ast::NodeKind::VariableDeclaration: resolve_variable_declaration(static_cast<ayla::ast::node::VariableDeclarationNode *>(node)); break;

  case ayla::ast::NodeKind::FunctionDeclaration: resolve_function_declaration(static_cast<ayla::ast::node::FunctionDeclarationNode *>(node)); break;

  case ayla::ast::NodeKind::ModuleDeclaration: resolve_module_declaration(static_cast<ayla::ast::node::ModuleDeclarationNode *>(node)); break;

  case ayla::ast::NodeKind::ReturnStatement: resolve_return_statement(static_cast<ayla::ast::node::ReturnStatementNode *>(node)); break;

  case ayla::ast::NodeKind::Assignment: resolve_assignment(static_cast<ayla::ast::node::AssignmentExpressionNode *>(node)); break;

  case ayla::ast::NodeKind::ArrayLiteral: resolve_array_literal(static_cast<ayla::ast::node::ArrayLiteralNode *>(node)); break;

  case ayla::ast::NodeKind::IndexAccess: resolve_index_access(static_cast<ayla::ast::node::IndexAccessNode *>(node)); break;

  case ayla::ast::NodeKind::ObjectLiteral: resolve_object_literal(static_cast<ayla::ast::node::ObjectLiteralNode *>(node)); break;

  case ayla::ast::NodeKind::Type: resolve_type_node(static_cast<ayla::ast::TypeNode *>(node)); break;

  case ayla::ast::NodeKind::UnaryExpression: resolve_unary_expression(static_cast<ayla::ast::node::UnaryExpressionNode *>(node)); break;

  default: break;
  }
}

void Resolver::push_scope() { current_scope = unit.scope_manager.create_scope(current_scope); }

void Resolver::pop_scope() { current_scope = current_scope->parent; }