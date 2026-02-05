#pragma once

#include "core/module/scope.hpp"
#include "core/node/Type.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "frontend/ast/AstNode.hpp"

struct Resolver {

  core::ParserScope *current_scope;
  CompilationUnit &unit;

  explicit Resolver(CompilationUnit &unit, core::ParserScope *global) : unit(unit), current_scope(global) {}

  void resolve(ayla::ast::AstNode *node);

  core::ParserScope *push_scope();
  void pop_scope();

  void resolve_top_level();

  void resolve_function_call(parser::node::FunctionCallNode *node);
  void resolve_assignment(parser::node::statement::AssignmentNode *node);

  void resolve_type(core::ast::TypeNode *type_node);
  void resolve_array_literal(parser::node::ASTArrayLiteralNode *node);
  void resolve_object_literal(parser::node::ObjectLiteralNode *node);
  void resolve_number_literal(parser::node::NumberLiteralNode *node);
  void resolve_string_literal(parser::node::StringLiteralNode *node);
  void resolve_boolean_literal(parser::node::BoolLiteralNode *node);
  void resolve_type_node(core::ast::TypeNode *node);

  void resolve_index_access(parser::node::IndexAccessNode *node);
  void resolve_member_access(parser::node::MemberAccessNode *node);

  void resolve_identifier(core::ast::IdentifierNode *node);
  void resolve_binary_expression(parser::node::BinaryExpressionNode *node);
  void resolve_if_statement(parser::node::IfStatementNode *node);
  void resolve_while_statement(parser::node::ASTWhileStatementNode *node);

  void resolve_variable_declaration(core::ast::PatternNode *node);
  void resolve_function_declaration(parser::node::FunctionDeclarationNode *node);
  void resolve_module_declaration(parser::node::statement::ModuleDeclarationNode *node);

  void resolve_block(parser::node::BlockStatementNode *node, bool create_scope = true);

  void resolve_return_statement(parser::node::ReturnStatementNode *node);

  void resolve_import_node(parser::node::statement::ImportNode *node);
  void resolve_expression_statement(core::ast::ExpressionStatementNode *node);

  void report_error(DiagnosticCode code, const SourceSlice &slice, const std::unordered_map<std::string, std::string> &ctx = {}) {
    auto *diag = unit.diagns.create(code, slice);

    for (auto &[k, v] : ctx) { diag->context.set(k, v); }
  }
};