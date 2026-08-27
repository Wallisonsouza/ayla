#pragma once

#include "celestia/ast/AstDispacher.hpp"
#include "celestia/ast/declarations/StructDeclaration.hpp"
#include "celestia/ast/expressions/IdentifierExpressionNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/semantic/scope/Scope.hpp"

#include "ContextStack.hpp"
#include "celestia/ast/declarations/CapabilityDeclaration.hpp"
#include "celestia/ast/declarations/FunctionDeclaration.hpp"
#include "celestia/ast/declarations/ImplementationDeclaration.hpp"
#include "celestia/ast/declarations/ImportDeclaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/declarations/VariableDeclaration.hpp"
#include "celestia/ast/expressions/AssignmentExpression.hpp"
#include "celestia/ast/expressions/BinaryExpressionNode.hpp"
#include "celestia/ast/expressions/CallExpressionNode.hpp"
#include "celestia/ast/expressions/IndexAcessExpressionNode.hpp"
#include "celestia/ast/expressions/LiteralExpressionNode.hpp"
#include "celestia/ast/expressions/MemberAccessExpressionNode.hpp"
#include "celestia/ast/expressions/UnaryExpressionNode.hpp"
#include "celestia/ast/patterns/NamedPatternNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/statements/ExpressionStatementNode.hpp"
#include "celestia/ast/statements/IfStatementNode.hpp"
#include "celestia/ast/statements/ReturnStatementNode.hpp"
#include "celestia/ast/statements/WhileStatementNode.hpp"
#include "celestia/ast/types/FunctionType.hpp"
namespace celestia::semantic {
struct ResolverContext {
  CompilerEnvironment &compiler;
  CompilationUnit &unit;

  ContextStack<core::Scope> scopes;

  celestia::ast::FunctionDeclaration *current_function = nullptr;
  celestia::ast::ModuleDeclaration *current_module = nullptr;
  celestia::ast::WhileStatement *current_loop = nullptr;

  Module &get_module() { return *unit.module; }

  ResolverContext(CompilerEnvironment &compiler, CompilationUnit &unit) : compiler(compiler), unit(unit), scopes(nullptr) {}
};

struct Resolver {

public:
  explicit Resolver(ResolverContext &context);
  void resolve(celestia::ast::Node *node);

private:
  AstDispatcher<Resolver, celestia::ast::Node> dispatcher;

  ResolverContext context;

  void bind_literals();
  void bind_expressions();
  void bind_statements();
  void bind_declarations();
  void bind_types();

  void resolve_named_type(ast::NamedType *node);
  void resolve_generic_type(ast::GenericTypeNode *node);
  void resolve_function_type(ast::FunctionType *node);

  void pattern(celestia::ast::PatternNode *pat, Visibility visibilit);

  void function_call(celestia::ast::CallExpressionNode *node);
  void assignment(celestia::ast::AssignmentExpressionNode *node);

  void array_literal(celestia::ast::ArrayLiteralNode *node);
  void object_literal(celestia::ast::ObjectLiteralNode *node);
  void struct_literal(ast::StructLiteralNode *node);
  // void number_literal(celestia::ast::NumberLiteralNode *node);
  // void string_literal(celestia::ast::StringLiteralNode *node);
  // void boolean_literal(celestia::ast::BoolLiteralNode *node);
  void type_node(celestia::ast::TypeNode *node);

  void index_access(celestia::ast::IndexAccessExpressionNode *node);
  void member_access(celestia::ast::MemberAccessExpressionNode *node);

  void identifier(celestia::ast::IdentifierExpressionNode *node);
  void binary_expression(celestia::ast::BinaryExpressionNode *node);
  void unary_expression(celestia::ast::UnaryExpressionNode *node);
  void if_statement(celestia::ast::IfStatement *node);

  void while_statement(celestia::ast::WhileStatement *node);

  void resolve_variable_declaration(celestia::ast::VariableDeclaration *node);
  void resolve_module_init_declaration(ast::ModuleInitDeclaration *node);

  void resolve_struct_declaration(celestia::ast::StructDeclaration *node);
  void resolve_field_declaration(celestia::ast::FieldDeclaration *node);
  void resolve_function_declaration(celestia::ast::FunctionDeclaration *node);
  void resolve_module_declaration(celestia::ast::ModuleDeclaration *node);
  void resolve_capability_declaration(celestia::ast::CapabilityDeclaration *node);
  void resolve_impl_declaration(celestia::ast::ImplDeclaration *node);
  void resolve_type_declaration(ast::TypeDeclaration *node);
  void block_statement(celestia::ast::BlockStatement *node);

  void return_statement(celestia::ast::ReturnStatement *node);

  void resolve_import_declaration(celestia::ast::ImportDeclaration *node);
  void expression_statement(celestia::ast::ExpressionStatement *node);
  bool can_have_visibility(core::ScopeKind kind, Visibility visibility);
  SymbolId declare_symbol(const std::string &name, SymbolKind kind, Visibility visibility, celestia::ast::Node *node);
  void named_pattern(celestia::ast::NamedPattern *pattern, Visibility visibilit);
};
} // namespace celestia::semantic