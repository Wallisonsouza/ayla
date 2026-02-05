#pragma once

#include "core/memory/BuiltinTypes.hpp"
#include "core/node/Type.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/literal_nodes.hpp"

#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/runtime/executor.hpp"
#include "frontend/ast/AstNode.hpp"

struct TypeChecker {

  CompilationUnit &unit;

  explicit TypeChecker(CompilationUnit &unit) : unit(unit) {}

  void check(ayla::ast::AstNode *node);

  void check_identifier(ayla::ast::IdentifierNode *node);
  void check_number_literal(ayla::ast::node::NumberLiteralNode *node) { node->inferred_type = &BuiltinTypes::Number; }
  void check_string_literal(ayla::ast::node::StringLiteralNode *node) { node->inferred_type = &BuiltinTypes::String; }
  void check_boolean_literal(ayla::ast::node::BoolLiteralNode *node) { node->inferred_type = &BuiltinTypes::Boolean; }

  void check_array_literal(parser::node::ASTArrayLiteralNode *node);
  void check_object_literal(parser::node::ObjectLiteralNode *node);

  void check_variable_declaration(ayla::ast::PatternNode *node);

  void check_function_declaration(parser::node::FunctionDeclarationNode *node);
  void check_function_call(ayla::ast::node::CallExpressionNode *node);

  // Expressões
  void check_binary_expression(ayla::ast::node::BinaryExpressionNode *node);
  void check_member_access(parser::node::MemberAccessNode *node);
  void check_index_access(parser::node::IndexAccessNode *node);

  // Controle
  void check_if_statement(parser::node::IfStatementNode *node);
  void check_while_statement(parser::node::ASTWhileStatementNode *node);
  void check_return_statement(parser::node::ReturnStatementNode *node);

  void check_block(parser::node::BlockStatementNode *node);

  void check_import_node(parser::node::statement::ImportNode *node);
  void check_module_declaration(parser::node::statement::ModuleDeclarationNode *node);
  void check_assignment(parser::node::statement::AssignmentNode *node);
  void check_expression_statement(ayla::ast::ExpressionStatementNode *node);
  void report_error(DiagnosticCode code, const SourceSlice &slice, const std::unordered_map<std::string, std::string> &ctx = {}) {
    auto *diag = unit.diagns.create(code, slice);
    for (auto &[k, v] : ctx) { diag->context.set(k, v); }
  }
};
