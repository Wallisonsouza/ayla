#include "Resolver.hpp"
#include "ayla-structural/ayla-ast/literal_nodes.hpp"
#include "ayla-structural/ayla-ast/statement_nodes.hpp"
#include "ayla-structural/ayla-ast/statements/ImportStatement.hpp"
#include "core/node/Type.hpp"
#include "core/node/flags.hpp"
#include <iostream>

void Resolver::resolve(core::ast::ASTNode *node) {

  if (!node || node->flags.has(NodeFlags::Resolved)) return;

  node->flags.set(NodeFlags::Resolved);

  switch (node->kind) {

  case core::ast::NodeKind::NumberLiteral: resolve_number_literal(static_cast<parser::node::NumberLiteralNode *>(node)); break;

  case core::ast::NodeKind::StringLiteral: resolve_string_literal(static_cast<parser::node::StringLiteralNode *>(node)); break;

  case core::ast::NodeKind::BooleanLiteral: resolve_boolean_literal(static_cast<parser::node::BoolLiteralNode *>(node)); break;

  case core::ast::NodeKind::IfStatement: resolve_if_statement(static_cast<parser::node::IfStatementNode *>(node)); break;

  case core::ast::NodeKind::WhileStatement: resolve_while_statement(static_cast<parser::node::ASTWhileStatementNode *>(node)); break;

  case core::ast::NodeKind::BlockStatement: resolve_block(static_cast<parser::node::BlockStatementNode *>(node)); break;

  case core::ast::NodeKind::BinaryExpression: resolve_binary_expression(static_cast<parser::node::BinaryExpressionNode *>(node)); break;

  case core::ast::NodeKind::MemberAccess: resolve_member_access(static_cast<parser::node::MemberAccessNode *>(node)); break;

  case core::ast::NodeKind::Import: resolve_import_node(static_cast<parser::node::statement::ImportNode *>(node)); break;

  case core::ast::NodeKind::Identifier: resolve_identifier(static_cast<core::ast::IdentifierNode *>(node)); break;

  case core::ast::NodeKind::FunctionCall: resolve_function_call(static_cast<parser::node::FunctionCallNode *>(node)); break;

  case core::ast::NodeKind::ExpressionStatement: resolve_expression_statement(static_cast<core::ast::ExpressionStatementNode *>(node)); break;

  case core::ast::NodeKind::VariableDeclaration: resolve_variable_declaration(static_cast<core::ast::PatternNode *>(node)); break;
  case core::ast::NodeKind::FunctionDeclaration: resolve_function_declaration(static_cast<parser::node::FunctionDeclarationNode *>(node)); break;
  case core::ast::NodeKind::ModuleDeclaration: resolve_module_declaration(static_cast<parser::node::statement::ModuleDeclarationNode *>(node)); break;

  case core::ast::NodeKind::ReturnStatement: resolve_return_statement(static_cast<parser::node::ReturnStatementNode *>(node)); break;

  case core::ast::NodeKind::Assignment: resolve_assignment(static_cast<parser::node::statement::AssignmentNode *>(node)); break;

  case core::ast::NodeKind::ArrayLiteral: resolve_array_literal(static_cast<parser::node::ASTArrayLiteralNode *>(node)); break;

  case core::ast::NodeKind::IndexAccess: resolve_index_access(static_cast<parser::node::IndexAccessNode *>(node)); break;

  case core::ast::NodeKind::ObjectLiteral: resolve_object_literal(static_cast<parser::node::ObjectLiteralNode *>(node)); break;

  case core::ast::NodeKind::Type: resolve_type_node(static_cast<core::ast::TypeNode *>(node)); break;

  default: break;
  }
}

void Resolver::push_scope() { current_scope = unit.scopes.create_scope(current_scope); }

void Resolver::enter_scope(core::ParserScope *scope) { current_scope = scope; }

void Resolver::leave_scope(core::ParserScope *previous) { current_scope = previous; }

void Resolver::pop_scope() {
  std::cout << "[pop ] scope=" << current_scope << "\n";
  current_scope = current_scope->parent;
}