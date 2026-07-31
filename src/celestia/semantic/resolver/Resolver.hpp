#pragma once

#include "celestia/ast/expressions/IdentifierExpressionNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/engine/CompilationUnit.hpp"
#include "celestia/engine/CompilerEnvironment.hpp"
#include "celestia/semantic/scope/Scope.hpp"

#include "Handler.hpp"
#include "celestia/ast/declarations/FunctionDeclarationNode.hpp"
#include "celestia/ast/declarations/ModuleDeclarationNode.hpp"
#include "celestia/ast/declarations/VariableDeclarationNode.hpp"
#include "celestia/ast/expressions/AssignmentExpression.hpp"
#include "celestia/ast/expressions/BinaryExpressionNode.hpp"
#include "celestia/ast/expressions/CallExpressionNode.hpp"
#include "celestia/ast/expressions/IndexAcessExpressionNode.hpp"
#include "celestia/ast/expressions/LiteralExpressionNode.hpp"
#include "celestia/ast/expressions/MemberAccessExpressionNode.hpp"
#include "celestia/ast/expressions/UnaryExpressionNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/statements/ExpressionStatementNode.hpp"
#include "celestia/ast/statements/IfStatementNode.hpp"
#include "celestia/ast/statements/ImportStatementNode.hpp"
#include "celestia/ast/statements/ReturnStatementNode.hpp"
#include "celestia/ast/statements/WhileStatementNode.hpp"
#include "ContextStack.hpp"

struct ResolverContext {
  CompilerEnvironment &compiler;
  CompilationUnit &unit;

  ContextStack<core::Scope> scopes;

  celestia::ast::node::FunctionDeclarationNode *current_function = nullptr;
  celestia::ast::node::ModuleDeclarationNode *current_module = nullptr;
  celestia::ast::node::WhileStatementNode *current_loop = nullptr;

  ResolverContext(CompilerEnvironment &compiler, CompilationUnit &unit) : compiler(compiler), unit(unit), scopes(nullptr) {}
};

struct Resolver {

public:
  explicit Resolver(ResolverContext &context);
  void resolve(celestia::ast::AstNode *node);

private:
  HandlerRegistry handlers;
  ResolverContext context;

  void pattern(celestia::ast::PatternNode *pat);

  void function_call(celestia::ast::node::CallExpressionNode *node);
  void assignment(celestia::ast::node::AssignmentExpressionNode *node);

  void array_literal(celestia::ast::node::ArrayLiteralNode *node);
  void object_literal(celestia::ast::node::ObjectLiteralNode *node);
  void number_literal(celestia::ast::node::NumberLiteralNode *node);
  void string_literal(celestia::ast::node::StringLiteralNode *node);
  void boolean_literal(celestia::ast::node::BoolLiteralNode *node);
  void type_node(celestia::ast::TypeNode *node);

  void index_access(celestia::ast::node::IndexAccessExpressionNode *node);
  void member_access(celestia::ast::node::MemberAccessExpressionNode *node);

  void identifier(celestia::ast::node::IdentifierExpressionNode *node);
  void binary_expression(celestia::ast::node::BinaryExpressionNode *node);
  void unary_expression(celestia::ast::node::UnaryExpressionNode *node);
  void if_statement(celestia::ast::node::IfStatementNode *node);
  void while_statement(celestia::ast::node::WhileStatementNode *node);

  void variable_declaration(celestia::ast::node::VariableDeclarationNode *node);
  void function_declaration(celestia::ast::node::FunctionDeclarationNode *node);
  void module_declaration(celestia::ast::node::ModuleDeclarationNode *node);

  void block(celestia::ast::node::BlockStatementNode *node);

  void return_statement(celestia::ast::node::ReturnStatementNode *node);

  void import_declaration(celestia::ast::node::ImportDeclarationNode *node);
  void expression_statement(celestia::ast::node::ExpressionStatementNode *node);

  void identifier_pattern(celestia::ast::IdentifierPatternNode *pattern);
};