#include "Resolver.hpp"
#include "core/node/Type.hpp"
#include "core/node/flags.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"

void Resolver::resolve(ayla::ast::AstNode *node) {

  if (!node || node->flags.has(NodeFlags::Resolved)) return;

  node->flags.set(NodeFlags::Resolved);

  switch (node->kind) {

  case ayla::ast::NodeKind::NumberLiteral: resolve_number_literal(static_cast<ayla::ast::node::NumberLiteralNode *>(node)); break;

  case ayla::ast::NodeKind::StringLiteral: resolve_string_literal(static_cast<ayla::ast::node::StringLiteralNode *>(node)); break;

  case ayla::ast::NodeKind::BooleanLiteral: resolve_boolean_literal(static_cast<ayla::ast::node::BoolLiteralNode *>(node)); break;

  case ayla::ast::NodeKind::IfStatement: resolve_if_statement(static_cast<parser::node::IfStatementNode *>(node)); break;

  case ayla::ast::NodeKind::WhileStatement: resolve_while_statement(static_cast<parser::node::ASTWhileStatementNode *>(node)); break;

  case ayla::ast::NodeKind::BlockStatement: resolve_block(static_cast<parser::node::BlockStatementNode *>(node)); break;

  case ayla::ast::NodeKind::BinaryExpression: resolve_binary_expression(static_cast<ayla::ast::node::BinaryExpressionNode *>(node)); break;

  case ayla::ast::NodeKind::MemberAccess: resolve_member_access(static_cast<parser::node::MemberAccessNode *>(node)); break;

  case ayla::ast::NodeKind::Import: resolve_import_node(static_cast<parser::node::statement::ImportNode *>(node)); break;

  case ayla::ast::NodeKind::Identifier: resolve_identifier(static_cast<ayla::ast::IdentifierNode *>(node)); break;

  case ayla::ast::NodeKind::FunctionCall: resolve_function_call(static_cast<ayla::ast::node::CallExpressionNode *>(node)); break;

  case ayla::ast::NodeKind::ExpressionStatement: resolve_expression_statement(static_cast<ayla::ast::ExpressionStatementNode *>(node)); break;

  case ayla::ast::NodeKind::VariableDeclaration: resolve_variable_declaration(static_cast<ayla::ast::PatternNode *>(node)); break;
  case ayla::ast::NodeKind::FunctionDeclaration: resolve_function_declaration(static_cast<parser::node::FunctionDeclarationNode *>(node)); break;
  case ayla::ast::NodeKind::ModuleDeclaration: resolve_module_declaration(static_cast<parser::node::statement::ModuleDeclarationNode *>(node)); break;

  case ayla::ast::NodeKind::ReturnStatement: resolve_return_statement(static_cast<parser::node::ReturnStatementNode *>(node)); break;

  case ayla::ast::NodeKind::Assignment: resolve_assignment(static_cast<parser::node::statement::AssignmentNode *>(node)); break;

  case ayla::ast::NodeKind::ArrayLiteral: resolve_array_literal(static_cast<parser::node::ASTArrayLiteralNode *>(node)); break;

  case ayla::ast::NodeKind::IndexAccess: resolve_index_access(static_cast<parser::node::IndexAccessNode *>(node)); break;

  case ayla::ast::NodeKind::ObjectLiteral: resolve_object_literal(static_cast<parser::node::ObjectLiteralNode *>(node)); break;

  case ayla::ast::NodeKind::Type: resolve_type_node(static_cast<ayla::ast::TypeNode *>(node)); break;

  default: break;
  }
}

core::ParserScope *Resolver::push_scope() {
  current_scope = unit.scope_manager.create_scope(current_scope);
  return current_scope;
}

void Resolver::pop_scope() { current_scope = current_scope->parent; }