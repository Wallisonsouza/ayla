#pragma once

#include "celestia/ast/Node.hpp"
#include "celestia/ast/declarations/FunctionDeclarationNode.hpp"
#include "celestia/ast/declarations/ModuleDeclarationNode.hpp"
#include "celestia/ast/declarations/VariableDeclarationNode.hpp"
#include "celestia/ast/expressions/AssignmentExpression.hpp"
#include "celestia/ast/expressions/BinaryExpressionNode.hpp"
#include "celestia/ast/expressions/CallExpressionNode.hpp"
#include "celestia/ast/expressions/IdentifierExpressionNode.hpp"
#include "celestia/ast/expressions/IndexAcessExpressionNode.hpp"
#include "celestia/ast/expressions/LiteralExpressionNode.hpp"
#include "celestia/ast/expressions/MemberAccessExpressionNode.hpp"
#include "celestia/ast/expressions/UnaryExpressionNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/statements/ExpressionStatementNode.hpp"
#include "celestia/ast/statements/IfStatementNode.hpp"
#include "celestia/ast/statements/ImportStatementNode.hpp"
#include "celestia/ast/statements/ReturnStatementNode.hpp"
#include "celestia/ast/statements/WhileStatementNode.hpp"
#include "celestia/core/visitor/AstStage.hpp"
#include "celestia/debug/ast/DumpContext.hpp"

#include <iostream>
#include <ostream>

class AstDumper : public AstStage {

public:
  AstDumper(std::ostream &out = std::cout) : context(out, [this](const celestia::ast::Node *node) { dispatch(node); }) { register_handlers(); }

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

  void dump_number_literal(const celestia::ast::NumberLiteralNode *node);

  void dump_string_literal(const celestia::ast::StringLiteralNode *node);

  void dump_bool_literal(const celestia::ast::BoolLiteralNode *node);

  void dump_null_literal(const celestia::ast::NullLiteralNode *node);

  // Names

  void dump_identifier(const celestia::ast::IdentifierNode *node);

  void dump_qualified_name(const celestia::ast::QualifiedNameNode *node);

  // Expressions

  void dump_identifier_expression(const celestia::ast::IdentifierExpressionNode *node);

  void dump_binary_expression(const celestia::ast::BinaryExpressionNode *node);

  void dump_unary_expression(const celestia::ast::UnaryExpressionNode *node);

  void dump_call_expression(const celestia::ast::CallExpressionNode *node);

  void dump_member_acess_expression(const celestia::ast::MemberAccessExpressionNode *node);

  void dump_index_acess_expression(const celestia::ast::IndexAccessExpressionNode *node);

  void dump_assignment_expression(const celestia::ast::AssignmentExpressionNode *node);
 
  // Statements

  void dump_expression_statement(const celestia::ast::ExpressionStatement *node);

  void dump_block_statement(const celestia::ast::BlockStatement *node);

  void dump_if_statement(const celestia::ast::IfStatement *node);

  void dump_while_statement(const celestia::ast::WhileStatement *node);

  void dump_return_statement(const celestia::ast::ReturnStatement *node);

  void dump_import_statement(const celestia::ast::ImportDeclarationNode *node);

  // Declarations

  void dump_variable_declaration(const celestia::ast::VariableDeclarationNode *node);

  void dump_function_declaration(const celestia::ast::FunctionDeclarationNode *node);

  void dump_module_declaration(const celestia::ast::ModuleDeclaration *node);

  // Other nodes

  void dump_identifier_pattern(const celestia::ast::IdentifierPatternNode *node);

  void dump_type(const celestia::ast::TypeNode *node);

  void dump_object_literal(const celestia::ast::ObjectLiteralNode *node);

  void dump_object_field(const celestia::ast::ObjectFieldNode *node);

  void dump_array_literal(const celestia::ast::ArrayLiteralNode *node);

  //---------

private:
  DumpContext context;
};
