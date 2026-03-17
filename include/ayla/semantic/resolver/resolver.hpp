#pragma once

#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/CompilationUnit.hpp"
#include "semantic/scope/scope.hpp"

#include "ayla/syntax/ast/ExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/AssignmentExpression.hpp"
#include "ayla/syntax/ast/expressions/BinaryExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/CallExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/IndexAcessExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/LiteralExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/MemberAccessExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/UnaryExpressionNode.hpp"
#include "ayla/syntax/ast/statements/ExpressionStatementNode.hpp"
#include "ayla/syntax/ast/statements/FunctionDeclarationNode.hpp"
#include "ayla/syntax/ast/statements/IfStatementNode.hpp"
#include "ayla/syntax/ast/statements/ImportStatementNode.hpp"
#include "ayla/syntax/ast/statements/ModuleDeclarationNode.hpp"
#include "ayla/syntax/ast/statements/ReturnStatementNodes.hpp"
#include "ayla/syntax/ast/statements/VariableDeclarationNode.hpp"
#include "ayla/syntax/ast/statements/WhileStatementNode.hpp"

namespace ayla::semantic {

struct Resolver {

  core::ParserScope *current_scope;
  CompilationUnit &unit;

  explicit Resolver(CompilationUnit &unit, core::ParserScope *global) : unit(unit), current_scope(global) {}

  void resolve(ayla::ast::AstNode *node);

  void push_scope();
  void pop_scope();

  void resolve_top_level();

  void resolve_pattern(ayla::ast::PatternNode *pat, ayla::ast::Modifiers modifier);

  void resolve_call_exp(ayla::ast::node::CallExpressionNode *node);
  void resolve_assign_exp(ayla::ast::node::AssignmentExpressionNode *node);

  void resolve_array_literal(ayla::ast::node::ArrayLiteralNode *node);
  void resolve_object_literal(ayla::ast::node::ObjectLiteralNode *node);
  void resolve_number_literal(ayla::ast::node::NumberLiteralNode *node);
  void resolve_string_literal(ayla::ast::node::StringLiteralNode *node);
  void resolve_boolean_literal(ayla::ast::node::BoolLiteralNode *node);
  void resolve_type_node(ayla::ast::TypeNode *node);

  void resolve_index_exp(ayla::ast::node::IndexAccessExpressionNode *node);
  void resolve_member_exp(ayla::ast::node::MemberAccessExpressionNode *node);

  void resolve_identifier_exp(ayla::ast::node::IdentifierExpressionNode *node);
  void resolve_binary_exp(ayla::ast::node::BinaryExpressionNode *node);
  void resolve_unary_exp(ayla::ast::node::UnaryExpressionNode *node);
  void resolve_if_statement(ayla::ast::node::IfStatementNode *node);
  void resolve_while_statement(ayla::ast::node::WhileStatementNode *node);

  void resolve_variable_declaration(ayla::ast::node::VariableDeclarationNode *node);
  void resolve_function_declaration(ayla::ast::node::FunctionDeclarationNode *node);
  void resolve_module_declaration(ayla::ast::node::ModuleDeclarationNode *node);

  void resolve_block_statement(ayla::ast::node::BlockStatementNode *node, bool create_scope = true);

  void resolve_return_statement(ayla::ast::node::ReturnStatementNode *node);

  void resolve_import_statement(ayla::ast::node::ImportStatementNode *node);
  void resolve_expression_statement(ayla::ast::node::ExpressionStatementNode *node);
};
} // namespace ayla::semantic
