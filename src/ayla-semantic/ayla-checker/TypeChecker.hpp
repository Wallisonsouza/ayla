#pragma once

#include "ayla-structural/ayla-ast/literal_nodes.hpp"
#include "ayla-structural/ayla-ast/operator_nodes.hpp"
#include "ayla-structural/ayla-ast/statement_nodes.hpp"
#include "ayla-structural/ayla-ast/statements/ImportStatement.hpp"
#include "core/memory/BuiltinTypes.hpp"
#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/CompilationUnit.hpp"

struct TypeChecker {

  CompilationUnit &unit;

  explicit TypeChecker(CompilationUnit &unit) : unit(unit) {}

  void check(core::ast::ASTNode *node);

  void check_identifier(core::ast::IdentifierNode *node);
  void check_number_literal(parser::node::NumberLiteralNode *node) { node->inferred_type = &BuiltinTypes::Number; }
  void check_string_literal(parser::node::StringLiteralNode *node) { node->inferred_type = &BuiltinTypes::String; }
  void check_boolean_literal(parser::node::BoolLiteralNode *node) { node->inferred_type = &BuiltinTypes::Boolean; }

  void check_array_literal(parser::node::ASTArrayLiteralNode *node);
  void check_object_literal(parser::node::ObjectLiteralNode *node);

  void check_variable_declaration(core::ast::PatternNode *node);

  void check_function_declaration(parser::node::FunctionDeclarationNode *node);
  void check_function_call(parser::node::FunctionCallNode *node);

  // Expressões
  void check_binary_expression(parser::node::BinaryExpressionNode *node);
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
  void check_expression_statement(core::ast::ExpressionStatementNode *node);
  void report_error(DiagnosticCode code, const SourceSlice &slice, const std::unordered_map<std::string, std::string> &ctx = {}) {
    auto *diag = unit.diagns.create(code, slice);
    for (auto &[k, v] : ctx) { diag->context.set(k, v); }
  }
};
