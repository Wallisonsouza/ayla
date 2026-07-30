#pragma once

#include "ast/expressions/IdentifierExpressionNode.hpp"
#include "ast/patterns/PatternNode.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/CompilerEnvironment.hpp"
#include "semantic/scope/Scope.hpp"

#include "Handler.hpp"
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
#include "ContextStack.hpp"

struct ResolverContext {
  CompilerEnvironment &compiler;
  CompilationUnit &unit;

  ContextStack<core::Scope> scopes;

  ayla::ast::node::FunctionDeclarationNode *current_function = nullptr;
  ayla::ast::node::ModuleDeclarationNode *current_module = nullptr;
  ayla::ast::node::WhileStatementNode *current_loop = nullptr;

  ResolverContext(CompilerEnvironment &compiler, CompilationUnit &unit) : compiler(compiler), unit(unit), scopes(nullptr) {}
};

struct Resolver {

public:
  explicit Resolver(ResolverContext &context);
  void resolve(ayla::ast::AstNode *node);

private:
  HandlerRegistry handlers;
  ResolverContext context;

  void pattern(ayla::ast::PatternNode *pat);

  void function_call(ayla::ast::node::CallExpressionNode *node);
  void assignment(ayla::ast::node::AssignmentExpressionNode *node);

  void array_literal(ayla::ast::node::ArrayLiteralNode *node);
  void object_literal(ayla::ast::node::ObjectLiteralNode *node);
  void number_literal(ayla::ast::node::NumberLiteralNode *node);
  void string_literal(ayla::ast::node::StringLiteralNode *node);
  void boolean_literal(ayla::ast::node::BoolLiteralNode *node);
  void type_node(ayla::ast::TypeNode *node);

  void index_access(ayla::ast::node::IndexAccessExpressionNode *node);
  void member_access(ayla::ast::node::MemberAccessExpressionNode *node);

  void identifier(ayla::ast::node::IdentifierExpressionNode *node);
  void binary_expression(ayla::ast::node::BinaryExpressionNode *node);
  void unary_expression(ayla::ast::node::UnaryExpressionNode *node);
  void if_statement(ayla::ast::node::IfStatementNode *node);
  void while_statement(ayla::ast::node::WhileStatementNode *node);

  void variable_declaration(ayla::ast::node::VariableDeclarationNode *node);
  void function_declaration(ayla::ast::node::FunctionDeclarationNode *node);
  void module_declaration(ayla::ast::node::ModuleDeclarationNode *node);

  void block(ayla::ast::node::BlockStatementNode *node);

  void return_statement(ayla::ast::node::ReturnStatementNode *node);

  void import_declaration(ayla::ast::node::ImportDeclarationNode *node);
  void expression_statement(ayla::ast::node::ExpressionStatementNode *node);

  void identifier_pattern(ayla::ast::IdentifierPatternNode *pattern);
};