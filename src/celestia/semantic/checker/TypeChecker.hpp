#pragma once

#include <iostream>
#include <ostream>

#include "celestia/ast/Node.hpp"

#include "celestia/ast/declarations/CapabilityDeclaration.hpp"
#include "celestia/ast/declarations/FunctionDeclaration.hpp"
#include "celestia/ast/declarations/ImplementationDeclaration.hpp"
#include "celestia/ast/declarations/ImportDeclaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/declarations/StructDeclaration.hpp"
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

#include "celestia/ast/types/Array.hpp"
#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/ast/types/ReferenceType.hpp"

#include "celestia/core/visitor/AstStage.hpp"
#include "celestia/semantic/resolver/Resolver.hpp"



namespace celestia::semantic {

class TypeChecker {
public:
  explicit TypeChecker(ResolverContext &context);

  void check(ast::Node *node);

private:
  ResolverContext &context;
  AstDispatcher dispatcher;

  void bind_literals();
  void bind_expressions();
  void bind_statements();
  void bind_declarations();
  void bind_types();

  // Literals
  void number_literal(ast::NumberLiteralNode *node);
  void string_literal(ast::StringLiteralNode *node);
  void boolean_literal(ast::BoolLiteralNode *node);
  void array_literal(ast::ArrayLiteralNode *node);

  // Expressions
  void binary_expression(ast::BinaryExpressionNode *node);
  void unary_expression(ast::UnaryExpressionNode *node);
  void assignment(ast::AssignmentExpressionNode *node);
  void function_call(ast::CallExpressionNode *node);
  void member_access(ast::MemberAccessExpressionNode *node);
  void index_access(ast::IndexAccessExpressionNode *node);
  void identifier(ast::IdentifierExpressionNode *node);

  // Statements
  void expression_statement(ast::ExpressionStatement *node);
  void return_statement(ast::ReturnStatement *node);
  void if_statement(ast::IfStatement *node);
  void while_statement(ast::WhileStatement *node);
  void block_statement(ast::BlockStatement *node);

  // Declarations
  void variable_declaration(ast::VariableDeclaration *node);
  void function_declaration(ast::FunctionDeclaration *node);

  // Types
  void type_node(ast::TypeNode *node);

  void error(ast::Node *node, std::string message){throw std::runtime_error(message);}
};

} // namespace celestia::semantic