#include "Resolver.hpp"
#include "core/node/Type.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include <iostream>

void Resolver::resolve(core::ast::ASTNode *node) {

  if (!node)
    return;

  switch (node->kind) {

  case core::ast::NodeKind::NumberLiteral:
  case core::ast::NodeKind::StringLiteral:
  case core::ast::NodeKind::BooleanLiteral:
    return;

  case core::ast::NodeKind::IfStatement:
    resolve_if_statement(static_cast<parser::node::IfStatementNode *>(node));
    break;

  case core::ast::NodeKind::WhileStatement:
    resolve_while_statement(
        static_cast<parser::node::ASTWhileStatementNode *>(node));
    break;

  case core::ast::NodeKind::BlockStatement:
    resolve_block(static_cast<parser::node::BlockStatementNode *>(node));
    break;

  case core::ast::NodeKind::BinaryExpression:
    resolve_binary_expression(
        static_cast<parser::node::BinaryExpressionNode *>(node));
    break;

  case core::ast::NodeKind::PathExpression:
    resolve_path(static_cast<parser::node::statement::PathExprNode *>(node));
    break;

  case core::ast::NodeKind::Import:
    resolve_import_node(
        static_cast<parser::node::statement::ImportNode *>(node));
    break;

  case core::ast::NodeKind::Identifier:
    resolve_identifier(static_cast<core::ast::IdentifierNode *>(node));
    break;

  case core::ast::NodeKind::FunctionCall:
    resolve_function_call(static_cast<parser::node::FunctionCallNode *>(node));
    break;

  case core::ast::NodeKind::VariableDeclaration:
    resolve_variable_declaration(static_cast<core::ast::PatternNode *>(node));
    break;

  case core::ast::NodeKind::NativeFunctionDeclaration:
    resolve_native_function_declaration(
        static_cast<core::ast::NativeFunctionDeclarationNode *>(node));
    break;

  case core::ast::NodeKind::ExpressionStatement:
    resolve_expression_statement(
        static_cast<core::ast::ExpressionStatementNode *>(node));
    break;

  case core::ast::NodeKind::FunctionDeclaration:
    resolve_function_declaration(
        static_cast<parser::node::FunctionDeclarationNode *>(node));
    break;

  case core::ast::NodeKind::ReturnStatement:
    resolve_return_statement(
        static_cast<parser::node::ReturnStatementNode *>(node));
    break;

  case core::ast::NodeKind::Assignment:
    resolve_assignment(
        static_cast<parser::node::statement::AssignmentNode *>(node));
    break;

  case core::ast::NodeKind::ArrayLiteral:
    resolve_array_literal(
        static_cast<parser::node::ASTArrayLiteralNode *>(node));
    break;

  default:
    break;
  }
}

void Resolver::resolve_ast() {
  resolve_top_level();

  for (auto *node : unit.ast.get_nodes()) {
    resolve(node);
  }
}

void Resolver::push_scope() {
  current_scope = unit.scopes.create_scope(current_scope);
  std::cout << "[push] scope=" << current_scope
            << " parent=" << current_scope->parent << "\n";
}

void Resolver::pop_scope() {
  std::cout << "[pop ] scope=" << current_scope << "\n";
  current_scope = current_scope->parent;
}