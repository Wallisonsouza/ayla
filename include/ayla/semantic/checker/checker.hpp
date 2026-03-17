#pragma once

#include "engine/CompilationUnit.hpp"
#include "semantic/types/BuiltinTypes.hpp"

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
struct Checker {

  CompilationUnit &unit;

  explicit Checker(CompilationUnit &unit) : unit(unit) {}

  void check(ast::AstNode *node);

  Type *current_function_return_type = nullptr;

  void check_id_expression(ast::node::IdentifierExpressionNode *node);

  void check_number_literal(ast::node::NumberLiteralNode *node) { node->inferred_type = &BuiltinTypes::Number; }

  void check_string_literal(ast::node::StringLiteralNode *node) { node->inferred_type = &BuiltinTypes::String; }

  void check_boolean_literal(ast::node::BoolLiteralNode *node) { node->inferred_type = &BuiltinTypes::Boolean; }

  void check_array_literal(ast::node::ArrayLiteralNode *node);

  void check_object_literal(ast::node::ObjectLiteralNode *node);

  void check_pattern(ast::PatternNode *node);

  void check_function_declaration(ast::node::FunctionDeclarationNode *node);
  void check_variable_declaration(ast::node::VariableDeclarationNode *node);
  void check_call_expression(ast::node::CallExpressionNode *node);

  // Expressões
  void check_binary_expression(ast::node::BinaryExpressionNode *node);
  void check_unary_expression(ast::node::UnaryExpressionNode *node);
  void check_member_expression(ast::node::MemberAccessExpressionNode *node);
  void check_index_expression(ast::node::IndexAccessExpressionNode *node);

  // Controle
  void check_if_statement(ast::node::IfStatementNode *node);
  void check_while_statement(ast::node::WhileStatementNode *node);
  void check_return_statement(ast::node::ReturnStatementNode *node);

  void check_block_statement(ast::node::BlockStatementNode *node);

  void check_import_statement(ast::node::ImportStatementNode *node);
  void check_module_declaration(ast::node::ModuleDeclarationNode *node);
  void check_assign_expression(ast::node::AssignmentExpressionNode *node);
  void check_expression_statement(ast::node::ExpressionStatementNode *node);
};
} // namespace ayla::semantic
