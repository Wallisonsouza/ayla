#pragma once

#include "core/module/scope.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/CompilationUnit.hpp"

#include "frontend/ast/AstNode.hpp"
#include "frontend/ast/expressions/AssignmentExpression.hpp"
#include "frontend/ast/expressions/BinaryExpressionNode.hpp"
#include "frontend/ast/expressions/CallExpressionNode.hpp"
#include "frontend/ast/expressions/IndexAcessExpressionNode.hpp"
#include "frontend/ast/expressions/LiteralExpressionNode.hpp"
#include "frontend/ast/expressions/MemberAccessExpressionNode.hpp"
#include "frontend/ast/statements/ExpressionStatementNode.hpp"
#include "frontend/ast/statements/IfStatementNode.hpp"
#include "frontend/ast/statements/ImportStatementNode.hpp"
#include "frontend/ast/statements/ModuleDeclarationNode.hpp"
#include "frontend/ast/statements/ReturnStatementNodes.hpp"
#include "frontend/ast/statements/VariableDeclarationNode.hpp"
#include "frontend/ast/statements/WhileStatementNode.hpp"

struct Resolver {

  core::ParserScope *current_scope;
  CompilationUnit &unit;

  explicit Resolver(CompilationUnit &unit, core::ParserScope *global) : unit(unit), current_scope(global) {}

  void resolve(ayla::ast::AstNode *node);

  void push_scope();
  void pop_scope();

  void resolve_top_level();

  void resolve_pattern(ayla::ast::PatternNode *pat);

  void resolve_function_call(ayla::ast::node::CallExpressionNode *node);
  void resolve_assignment(ayla::ast::node::AssignmentExpressionNode *node);

  void resolve_type(ayla::ast::TypeNode *type_node);
  void resolve_array_literal(ayla::ast::node::ArrayLiteralNode *node);
  void resolve_object_literal(ayla::ast::node::ObjectLiteralNode *node);
  void resolve_number_literal(ayla::ast::node::NumberLiteralNode *node);
  void resolve_string_literal(ayla::ast::node::StringLiteralNode *node);
  void resolve_boolean_literal(ayla::ast::node::BoolLiteralNode *node);
  void resolve_type_node(ayla::ast::TypeNode *node);

  void resolve_index_access(ayla::ast::node::IndexAccessNode *node);
  void resolve_member_access(ayla::ast::node::MemberAccessExpressionNode *node);

  void resolve_identifier(ayla::ast::node::IdentifierExpressionNode *node);
  void resolve_binary_expression(ayla::ast::node::BinaryExpressionNode *node);
  void resolve_if_statement(ayla::ast::node::IfStatementNode *node);
  void resolve_while_statement(ayla::ast::node::WhileStatementNode *node);

  void resolve_variable_declaration(ayla::ast::node::VariableDeclarationNode *node);
  void resolve_function_declaration(ayla::ast::node::FunctionDeclarationNode *node);
  void resolve_module_declaration(ayla::ast::node::ModuleDeclarationNode *node);

  void resolve_block(ayla::ast::node::BlockStatementNode *node, bool create_scope = true);

  void resolve_return_statement(ayla::ast::node::ReturnStatementNode *node);

  void resolve_import_node(ayla::ast::node::ImportStatementNode *node);
  void resolve_expression_statement(ayla::ast::node::ExpressionStatementNode *node);

  void report_error(DiagnosticCode code, const SourceSlice &slice, const std::unordered_map<std::string, std::string> &ctx = {}) {
    auto *diag = unit.diagns.create(code, slice);

    for (auto &[k, v] : ctx) { diag->context.set(k, v); }
  }
};