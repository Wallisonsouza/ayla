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

namespace celestia::semantic {

class TypeChecker : public AstStage {

public:

  // ========================================================
  // Expressions

  void number_literal(ast::NumberLiteralNode *node);

  void string_literal(ast::StringLiteralNode *node);

  void boolean_literal(ast::BoolLiteralNode *node);

  void null_literal(ast::NullLiteralNode *node);

  void array_literal(ast::ArrayLiteralNode *node);

  void object_literal(ast::ObjectLiteralNode *node);

  void struct_literal(ast::StructLiteralNode *node);

  void identifier(ast::IdentifierExpressionNode *node);

  void binary_expression(ast::BinaryExpressionNode *node);

  void unary_expression(ast::UnaryExpressionNode *node);

  void call_expression(ast::CallExpressionNode *node);

  void member_access(ast::MemberAccessExpressionNode *node);

  void index_access(ast::IndexAccessExpressionNode *node);

  // ========================================================
  // Declarations
  // ========================================================

  void variable_declaration(ast::VariableDeclaration *node);

  void function_declaration(ast::FunctionDeclaration *node);

  void struct_declaration(ast::StructDeclaration *node);

  // ========================================================
  // Types
  // ========================================================

  void named_type(ast::NamedType *node);

  void array_type(ast::ArrayType *node);

  void reference_type(ast::ReferenceType *node);

  void generic_type(ast::GenericType *node);

private:

  CompilationUnit &unit;
  // ========================================================
  // Type helpers
  // ========================================================

  ast::TypeNode *type_of(ast::Expression *expression);

  bool same_type(const ast::TypeNode *a, const ast::TypeNode *b);

  bool is_assignable(const ast::TypeNode *from, const ast::TypeNode *to);

  ast::ArrayType *make_array_type(ast::TypeNode *element_type);
};

} // namespace celestia::semantic