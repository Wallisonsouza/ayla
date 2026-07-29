#pragma once

#include "ast/declarations/FunctionDeclarationNode.hpp"
#include "ast/declarations/ModuleDeclarationNode.hpp"
#include "ast/declarations/VariableDeclarationNode.hpp"
#include "ast/expressions/AssignmentExpression.hpp"
#include "ast/expressions/BinaryExpressionNode.hpp"
#include "ast/expressions/CallExpressionNode.hpp"
#include "ast/expressions/IdentifierExpressionNode.hpp"
#include "ast/expressions/IndexAcessExpressionNode.hpp"
#include "ast/expressions/LiteralExpressionNode.hpp"
#include "ast/expressions/MemberAccessExpressionNode.hpp"
#include "ast/expressions/UnaryExpressionNode.hpp"
#include "ast/patterns/PatternNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "ast/statements/ExpressionStatementNode.hpp"
#include "ast/statements/IfStatementNode.hpp"
#include "ast/statements/ImportStatementNode.hpp"
#include "ast/statements/ReturnStatementNode.hpp"
#include "ast/statements/WhileStatementNode.hpp"
#include "core/visitor/AstStage.hpp"
#include "debug/ast/DumpContext.hpp"

#include <iostream>
#include <ostream>

class AstDumper : public AstStage {

public:
  AstDumper(std::ostream &out = std::cout) : context(out, [this](const ayla::ast::AstNode *node) { dispatch(node); }) { register_handlers(); }

  public: void dump_scrypt() {
    
  }
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

  void dump_number_literal(const ayla::ast::node::NumberLiteralNode *node);

  void dump_string_literal(const ayla::ast::node::StringLiteralNode *node);

  void dump_bool_literal(const ayla::ast::node::BoolLiteralNode *node);

  void dump_null_literal(const ayla::ast::node::NullLiteralNode *node);

  // Names

  void dump_identifier(const ayla::ast::IdentifierNode *node);

  void dump_qualified_name(const ayla::ast::QualifiedNameNode *node);

  // Expressions

  void dump_identifier_expression(const ayla::ast::node::IdentifierExpressionNode *node);

  void dump_binary_expression(const ayla::ast::node::BinaryExpressionNode *node);

  void dump_unary_expression(const ayla::ast::node::UnaryExpressionNode *node);

  void dump_call_expression(const ayla::ast::node::CallExpressionNode *node);

  void dump_member_acess_expression(const ayla::ast::node::MemberAccessExpressionNode *node);

  void dump_index_acess_expression(const ayla::ast::node::IndexAccessExpressionNode *node);

  void dump_assignment_expression(const ayla::ast::node::AssignmentExpressionNode *node);
 
  // Statements

  void dump_expression_statement(const ayla::ast::node::ExpressionStatementNode *node);

  void dump_block_statement(const ayla::ast::node::BlockStatementNode *node);

  void dump_if_statement(const ayla::ast::node::IfStatementNode *node);

  void dump_while_statement(const ayla::ast::node::WhileStatementNode *node);

  void dump_return_statement(const ayla::ast::node::ReturnStatementNode *node);

  void dump_import_statement(const ayla::ast::node::ImportDeclarationNode *node);

  // Declarations

  void dump_variable_declaration(const ayla::ast::node::VariableDeclarationNode *node);

  void dump_function_declaration(const ayla::ast::node::FunctionDeclarationNode *node);

  void dump_module_declaration(const ayla::ast::node::ModuleDeclarationNode *node);

  // Other nodes

  void dump_identifier_pattern(const ayla::ast::IdentifierPatternNode *node);

  void dump_type(const ayla::ast::TypeNode *node);

  void dump_object_literal(const ayla::ast::node::ObjectLiteralNode *node);

  void dump_object_field(const ayla::ast::node::ObjectFieldNode *node);

  void dump_array_literal(const ayla::ast::node::ArrayLiteralNode *node);

  //---------

private:
  DumpContext context;
};
