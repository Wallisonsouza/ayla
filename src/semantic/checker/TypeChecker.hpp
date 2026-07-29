#pragma once

#include "ast/AstNode.hpp"
#include "ast/expressions/IdentifierExpressionNode.hpp"
#include "core/token/Location.hpp"
#include "diagnostic/DiagnosticCode.hpp"
#include "engine/CompilationUnit.hpp"
#include "semantic/types/BuiltinTypes.hpp"

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

struct CheckerContext {};

namespace ayla {
class TypeChecker {

public:
  CompilationUnit &unit;

  explicit TypeChecker(CompilationUnit &unit) : unit(unit) {}
void check(ast::AstNode *node);

private:
  

  void check_identifier(ast::node::IdentifierExpressionNode *node);

  void check_number_literal(ast::node::NumberLiteralNode *node) { node->inferred_type = &BuiltinTypes::Number; }

  void check_string_literal(ast::node::StringLiteralNode *node) { node->inferred_type = &BuiltinTypes::String; }

  void check_boolean_literal(ast::node::BoolLiteralNode *node) { node->inferred_type = &BuiltinTypes::Boolean; }

  void check_array_literal(ast::node::ArrayLiteralNode *node);

  void check_object_literal(ast::node::ObjectLiteralNode *node);

  void check_pattern(ast::PatternNode *node);

  void check_function_declaration(ast::node::FunctionDeclarationNode *node);
  void check_variable_declaration(ast::node::VariableDeclarationNode *node);
  void check_function_call(ast::node::CallExpressionNode *node);

  // Expressões
  void check_binary_expression(ast::node::BinaryExpressionNode *node);
  void check_unary_expression(ast::node::UnaryExpressionNode *node);
  void check_member_access(ast::node::MemberAccessExpressionNode *node);
  void check_index_access(ast::node::IndexAccessExpressionNode *node);

  // Controle
  void check_if_statement(ast::node::IfStatementNode *node);
  void check_while_statement(ast::node::WhileStatementNode *node);
  void check_return_statement(ast::node::ReturnStatementNode *node);

  void check_block(ast::node::BlockStatementNode *node);

  void check_import_declaration_node(ast::node::ImportDeclarationNode *node);
  void check_module_declaration(ast::node::ModuleDeclarationNode *node);
  void check_assignment(ast::node::AssignmentExpressionNode *node);
  void check_expression_statement(ast::node::ExpressionStatementNode *node);

  void report_error(diagnostic::DiagnosticCode vode, SourceSlice slice) {};
};
} // namespace ayla
