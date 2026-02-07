#pragma once

#include "core/memory/BuiltinTypes.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/CompilationUnit.hpp"
#include <iostream>

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

struct TypeChecker {

  CompilationUnit &unit;

  explicit TypeChecker(CompilationUnit &unit) : unit(unit) {}

  void check(ayla::ast::AstNode *node);

  void check_identifier(ayla::ast::node::IdentifierExpressionNode *node);

  void check_number_literal(ayla::ast::node::NumberLiteralNode *node) { node->inferred_type = &BuiltinTypes::Number; }

  void check_string_literal(ayla::ast::node::StringLiteralNode *node) { node->inferred_type = &BuiltinTypes::String; }

  void check_boolean_literal(ayla::ast::node::BoolLiteralNode *node) { node->inferred_type = &BuiltinTypes::Boolean; }

  void check_array_literal(ayla::ast::node::ArrayLiteralNode *node);

  void check_object_literal(ayla::ast::node::ObjectLiteralNode *node);

  void check_pattern(ayla::ast::PatternNode *node);

  void check_function_declaration(ayla::ast::node::FunctionDeclarationNode *node);
  void check_variable_declaration(ayla::ast::node::VariableDeclarationNode *node);
  void check_function_call(ayla::ast::node::CallExpressionNode *node);

  // Expressões
  void check_binary_expression(ayla::ast::node::BinaryExpressionNode *node);
  void check_member_access(ayla::ast::node::MemberAccessExpressionNode *node);
  void check_index_access(ayla::ast::node::IndexAccessNode *node);

  // Controle
  void check_if_statement(ayla::ast::node::IfStatementNode *node);
  void check_while_statement(ayla::ast::node::WhileStatementNode *node);
  void check_return_statement(ayla::ast::node::ReturnStatementNode *node);

  void check_block(ayla::ast::node::BlockStatementNode *node);

  void check_import_node(ayla::ast::node::ImportStatementNode *node);
  void check_module_declaration(ayla::ast::node::ModuleDeclarationNode *node);
  void check_assignment(ayla::ast::node::AssignmentExpressionNode *node);
  void check_expression_statement(ayla::ast::node::ExpressionStatementNode *node);

  void report_error(DiagnosticCode code, const SourceSlice &slice, const std::unordered_map<std::string, std::string> &ctx = {}) {
    auto *diag = unit.diagns.create(code, slice);
    for (auto &[k, v] : ctx) { diag->context.set(k, v); }
  }
};
