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

#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"

#include "celestia/semantic/resolver/Resolver.hpp"

namespace celestia::semantic {

class TypeChecker {
public:
  explicit TypeChecker(ResolverContext &context);

  void check(ast::Node *node);

private:
  ResolverContext &context;
  AstDispatcher<TypeChecker, celestia::ast::Node> dispatcher;

  void bind_literals();
  void bind_expressions();
  void bind_statements();
  void bind_declarations();
  void bind_types();

  TypeId current_function = TypeId::invalid();

  TypeId create_function_type(ast::FunctionDeclaration *node);

  TypeId check_generic_type(ast::GenericTypeNode *node);

  TypeId check_named_type(ast::NamedType *node);

  TypeId check_generic_instance_type(ast::GenericTypeNode *node);

  bool check_function_parameters(ast::FunctionDeclaration *node, FunctionType &function_type);

  bool check_function_return_type(ast::FunctionDeclaration *node, FunctionType &function_type);

  void check_function_body(ast::FunctionDeclaration *node, TypeId function_type);

  // Literals
  bool is_same_type(TypeId a, TypeId b) const;
  bool is_assignable(TypeId target, TypeId source) const;

  void number_literal(ast::NumberLiteralNode *node);
  void string_literal(ast::StringLiteralNode *node);
  void boolean_literal(ast::BoolLiteralNode *node);
  void array_literal(ast::ArrayLiteralNode *node);
  void check_struct_literal(ast::StructLiteralNode *node);

  TypeId check_pattern(ast::PatternNode *pattern, TypeId expected_type = TypeId::invalid());

  TypeId check_name_pattern(ast::NamedPattern *pattern, TypeId);

  // Expressions
  void binary_expression(ast::BinaryExpressionNode *node);
  void unary_expression(ast::UnaryExpressionNode *node);
  void assignment(ast::AssignmentExpressionNode *node);
  void function_call(ast::CallExpressionNode *node);
  void member_access(ast::MemberAccessExpressionNode *node);
  void index_access(ast::IndexAccessExpressionNode *node);
  void identifier(ast::IdentifierExpressionNode *node);

  // Statements
  void check_expression_statement(ast::ExpressionStatement *node);
  void check_return_statement(ast::ReturnStatement *node);
  void check_if_statement(ast::IfStatement *node);
  void check_while_statement(ast::WhileStatement *node);
  void check_block_statement(ast::BlockStatement *node);

  // Declarations
  void check_variable_declaration(ast::VariableDeclaration *node);
  void check_function_declaration(ast::FunctionDeclaration *node);
  void check_struct_declaration(ast::StructDeclaration *node);
  void function_declaration(ast::FunctionDeclaration *node);
  void check_module_declaration(ast::ModuleDeclaration *node);
  void check_module_init_declaration(ast::ModuleInitDeclaration *node);
  // Types
  void type_node(ast::TypeNode *node);
  TypeId type_from_node(ast::TypeNode *node);
  void error(ast::Node *node, std::string message) { throw std::runtime_error(message); }
};

} // namespace celestia::semantic