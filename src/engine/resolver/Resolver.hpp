#pragma once
#include "core/module/scope.hpp"
#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"

struct Resolver {

  core::Scope *current_scope;

  CompilationUnit &unit;

  explicit Resolver(CompilationUnit &unit, core::Scope *global) : unit(unit), current_scope(global) {}

  void resolve(core::ast::ASTNode *node);
  void push_scope();
  void pop_scope();

  void resolve_top_level();

  void resolve_function_call(parser::node::FunctionCallNode *node);
  void resolve_assignment(parser::node::statement::AssignmentNode *node);
  void resolve_array_literal(parser::node::ASTArrayLiteralNode *node);
  void resolve_identifier(core::ast::IdentifierNode *node);
  void resolve_binary_expression(parser::node::BinaryExpressionNode *node);
  void resolve_if_statement(parser::node::IfStatementNode *node);
  void resolve_while_statement(parser::node::ASTWhileStatementNode *node);
  void resolve_variable_declaration(core::ast::PatternNode *node);
  void resolve_function_declaration(parser::node::FunctionDeclarationNode *node);
  void resolve_native_function_declaration(core::ast::NativeFunctionDeclarationNode *node);

  void resolve_block(parser::node::BlockStatementNode *node, bool create_scope = true);

  void resolve_return_statement(parser::node::ReturnStatementNode *node);

  void resolve_path(parser::node::statement::PathExprNode *node);
  void resolve_import_node(parser::node::statement::ImportNode *node);
  void resolve_expression_statement(core::ast::ExpressionStatementNode *node);
  void resolve_ast();

  void report_error(DiagnosticCode code, const SourceSlice &slice, const std::unordered_map<std::string, std::string> &ctx = {}) {
    auto *diag = unit.diagns.create(code, slice);

    for (auto &[k, v] : ctx) { diag->context.set(k, v); }
  }
};