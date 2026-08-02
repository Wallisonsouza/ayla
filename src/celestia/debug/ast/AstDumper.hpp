#pragma once

#include <iostream>
#include <ostream>

#include "celestia/ast/Node.hpp"
#include "celestia/ast/declarations/FunctionDeclaration.hpp"
#include "celestia/ast/declarations/ImportDeclaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/declarations/VariableDeclaration.hpp"
#include "celestia/ast/expressions/AssignmentExpression.hpp"
#include "celestia/ast/expressions/BinaryExpressionNode.hpp"
#include "celestia/ast/expressions/CallExpressionNode.hpp"
#include "celestia/ast/expressions/IdentifierExpressionNode.hpp"
#include "celestia/ast/expressions/IndexAcessExpressionNode.hpp"
#include "celestia/ast/expressions/LiteralExpressionNode.hpp"
#include "celestia/ast/expressions/MemberAccessExpressionNode.hpp"
#include "celestia/ast/expressions/UnaryExpressionNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/statements/ExpressionStatementNode.hpp"
#include "celestia/ast/statements/IfStatementNode.hpp"
#include "celestia/ast/statements/ReturnStatementNode.hpp"
#include "celestia/ast/statements/WhileStatementNode.hpp"
#include "celestia/core/visitor/AstStage.hpp"
#include "celestia/debug/ast/DumpContext.hpp"

namespace celestia::debug {
class AstDumper : public AstStage {

public:
  AstDumper(std::ostream &out = std::cout) : context(out, [this](const celestia::ast::Node *node) { dispatch(node); }) { register_handlers(); }

public:
  void dump_scrypt() {}

private:
  void register_handlers() {
    bind(&AstDumper::dump_number_literal);
    bind(&AstDumper::dump_string_literal);
    bind(&AstDumper::dump_bool_literal);
    bind(&AstDumper::dump_null_literal);

    // Names
    bind(&AstDumper::dump_identifier);
    bind(&AstDumper::dump_qualified_name);

    // Expressions
    bind(&AstDumper::dump_identifier_expression);
    bind(&AstDumper::dump_binary_expression);
    bind(&AstDumper::dump_unary_expression);
    bind(&AstDumper::dump_call_expression);
    bind(&AstDumper::dump_member_acess_expression);
    bind(&AstDumper::dump_index_acess_expression);
    bind(&AstDumper::dump_assignment_expression);

    // Statements
    bind(&AstDumper::dump_expression_statement);
    bind(&AstDumper::dump_block_statement);
    bind(&AstDumper::dump_if_statement);
    bind(&AstDumper::dump_while_statement);
    bind(&AstDumper::dump_return_statement);
    bind(&AstDumper::dump_import_statement);

    // Declarations
    bind(&AstDumper::dump_variable_declaration);
    bind(&AstDumper::dump_function_declaration);
    bind(&AstDumper::dump_module_declaration);

    // Other nodes
    bind(&AstDumper::dump_identifier_pattern);
    bind(&AstDumper::dump_type);
    bind(&AstDumper::dump_object_literal);
    bind(&AstDumper::dump_object_field);
    bind(&AstDumper::dump_array_literal);
  }

  void dump_number_literal(const ast::NumberLiteralNode *node);

  void dump_string_literal(const ast::StringLiteralNode *node);

  void dump_bool_literal(const ast::BoolLiteralNode *node);

  void dump_null_literal(const ast::NullLiteralNode *node);

  // Names

  void dump_identifier(const ast::IdentifierNode *node);

  void dump_qualified_name(const ast::QualifiedNameNode *node);

  // Expressions

  void dump_identifier_expression(const ast::IdentifierExpressionNode *node);

  void dump_binary_expression(const ast::BinaryExpressionNode *node);

  void dump_unary_expression(const ast::UnaryExpressionNode *node);

  void dump_call_expression(const ast::CallExpressionNode *node);

  void dump_member_acess_expression(const ast::MemberAccessExpressionNode *node);

  void dump_index_acess_expression(const ast::IndexAccessExpressionNode *node);

  void dump_assignment_expression(const ast::AssignmentExpressionNode *node);

  // Statements

  void dump_expression_statement(const ast::ExpressionStatement *node);

  void dump_block_statement(const ast::BlockStatement *node);

  void dump_if_statement(const ast::IfStatement *node);

  void dump_while_statement(const ast::WhileStatement *node);

  void dump_return_statement(const ast::ReturnStatement *node);

  void dump_import_statement(const ast::ImportDeclaration *node);

  // Declarations

  void dump_variable_declaration(const ast::VariableDeclaration *node);

  void dump_function_declaration(const ast::FunctionDeclaration *node);

  void dump_module_declaration(const ast::ModuleDeclaration *node);

  // Other nodes

  void dump_identifier_pattern(const ast::IdentifierPatternNode *node);

  void dump_type(const ast::TypeNode *node);

  void dump_object_literal(const ast::ObjectLiteralNode *node);

  void dump_object_field(const ast::ObjectFieldNode *node);

  void dump_array_literal(const ast::ArrayLiteralNode *node);

  //---------

private:
  DumpContext context;
};

} // namespace celestia::debug
