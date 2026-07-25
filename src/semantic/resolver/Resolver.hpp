#pragma once

#include "ast/expressions/IdentifierExpressionNode.hpp"
#include "core/modifiers/ModifierSet.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/CompilationUnit.hpp"
#include "semantic/scope/Scope.hpp"

#include "ast/declarations/FunctionDeclarationNode.hpp"
#include "ast/declarations/ModuleDeclarationNode.hpp"
#include "ast/declarations/VariableDeclarationNode.hpp"
#include "ast/expressions/AssignmentExpression.hpp"
#include "ast/expressions/BinaryExpressionNode.hpp"
#include "ast/expressions/CallExpressionNode.hpp"
#include "ast/expressions/IndexAcessExpressionNode.hpp"
#include "ast/expressions/LiteralExpressionNode.hpp"
#include "ast/expressions/MemberAccessExpressionNode.hpp"
#include "ast/expressions/UnaryExpressionNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "ast/statements/ExpressionStatementNode.hpp"
#include "ast/statements/IfStatementNode.hpp"
#include "ast/statements/ImportStatementNode.hpp"
#include "ast/statements/ReturnStatementNode.hpp"
#include "ast/statements/WhileStatementNode.hpp"

struct Resolver {

  core::Scope *current_scope;
  CompilationUnit &unit;

  explicit Resolver(CompilationUnit &unit, core::Scope *global) : unit(unit), current_scope(global) {}

  void resolve(ayla::ast::AstNode *node);

  void push_scope();
  void pop_scope();

  void resolve_pattern(ayla::ast::PatternNode *pat, ModifierSet modifier);

  void resolve_function_call(ayla::ast::node::CallExpressionNode *node);
  void resolve_assignment(ayla::ast::node::AssignmentExpressionNode *node);

  void resolve_array_literal(ayla::ast::node::ArrayLiteralNode *node);
  void resolve_object_literal(ayla::ast::node::ObjectLiteralNode *node);
  void resolve_number_literal(ayla::ast::node::NumberLiteralNode *node);
  void resolve_string_literal(ayla::ast::node::StringLiteralNode *node);
  void resolve_boolean_literal(ayla::ast::node::BoolLiteralNode *node);
  void resolve_type_node(ayla::ast::TypeNode *node);

  void resolve_index_access(ayla::ast::node::IndexAccessExpressionNode *node);
  void resolve_member_access(ayla::ast::node::MemberAccessExpressionNode *node);

  void resolve_identifier(ayla::ast::node::IdentifierExpressionNode *node);
  void resolve_binary_expression(ayla::ast::node::BinaryExpressionNode *node);
  void resolve_unary_expression(ayla::ast::node::UnaryExpressionNode *node);
  void resolve_if_statement(ayla::ast::node::IfStatementNode *node);
  void resolve_while_statement(ayla::ast::node::WhileStatementNode *node);

  void resolve_variable_declaration(ayla::ast::node::VariableDeclarationNode *node);
  void resolve_function_declaration(ayla::ast::node::FunctionDeclarationNode *node);
  void resolve_module_declaration(ayla::ast::node::ModuleDeclarationNode *node);

  void resolve_block(ayla::ast::node::BlockStatementNode *node, bool create_scope = true);

  void resolve_return_statement(ayla::ast::node::ReturnStatementNode *node);

  void resolve_import_node(ayla::ast::node::ImportDeclarationNode *node);
  void resolve_expression_statement(ayla::ast::node::ExpressionStatementNode *node);
};