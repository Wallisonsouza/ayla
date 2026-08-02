#pragma once

#include "celestia/ast/NodeKind.hpp"

// Declarations
#include "celestia/ast/declarations/FunctionDeclaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/declarations/VariableDeclaration.hpp"
#include "celestia/ast/declarations/ImportDeclaration.hpp"
// Expressions
#include "celestia/ast/expressions/AssignmentExpression.hpp"
#include "celestia/ast/expressions/BinaryExpressionNode.hpp"
#include "celestia/ast/expressions/CallExpressionNode.hpp"
#include "celestia/ast/expressions/IdentifierExpressionNode.hpp"
#include "celestia/ast/expressions/IndexAcessExpressionNode.hpp"
#include "celestia/ast/expressions/LiteralExpressionNode.hpp"
#include "celestia/ast/expressions/MemberAccessExpressionNode.hpp"
#include "celestia/ast/expressions/UnaryExpressionNode.hpp"
// Statements
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/statements/ExpressionStatementNode.hpp"
#include "celestia/ast/statements/IfStatementNode.hpp"
#include "celestia/ast/statements/ReturnStatementNode.hpp"
#include "celestia/ast/statements/WhileStatementNode.hpp"
// Names
#include "celestia/ast/names/IdentifierNode.hpp"
#include "celestia/ast/names/QualifiedNameNode.hpp"

// Types
#include "celestia/ast/TypeNode.hpp"

// Patterns
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/ast/patterns/IdentifierPatternNode.hpp"

namespace celestia::ast {

template <typename T> struct NodeTraits;

// =====================
// Declarations
// =====================

template <> struct NodeTraits<FunctionDeclaration> {
  static constexpr NodeKind kind = NodeKind::FunctionDeclaration;
};

template <> struct NodeTraits<VariableDeclaration> {
  static constexpr NodeKind kind = NodeKind::VariableDeclaration;
};

template <> struct NodeTraits<ModuleDeclaration> {
  static constexpr NodeKind kind = NodeKind::ModuleDeclaration;
};

// =====================
// Expressions
// =====================

template <> struct NodeTraits<BinaryExpressionNode> {
  static constexpr NodeKind kind = NodeKind::BinaryExpression;
};

template <> struct NodeTraits<UnaryExpressionNode> {
  static constexpr NodeKind kind = NodeKind::UnaryExpression;
};

template <> struct NodeTraits<CallExpressionNode> {
  static constexpr NodeKind kind = NodeKind::Call;
};

template <> struct NodeTraits<AssignmentExpressionNode> {
  static constexpr NodeKind kind = NodeKind::Assignment;
};

template <> struct NodeTraits<MemberAccessExpressionNode> {
  static constexpr NodeKind kind = NodeKind::MemberAccess;
};

template <> struct NodeTraits<IndexAccessExpressionNode> {
  static constexpr NodeKind kind = NodeKind::IndexAccess;
};

template <> struct NodeTraits<IdentifierExpressionNode> {
  static constexpr NodeKind kind = NodeKind::IdentifierExpression;
};

// =====================
// Literals
// =====================

template <> struct NodeTraits<NumberLiteralNode> {
  static constexpr NodeKind kind = NodeKind::NumberLiteral;
};

template <> struct NodeTraits<StringLiteralNode> {
  static constexpr NodeKind kind = NodeKind::StringLiteral;
};

template <> struct NodeTraits<BoolLiteralNode> {
  static constexpr NodeKind kind = NodeKind::BooleanLiteral;
};

template <> struct NodeTraits<NullLiteralNode> {
  static constexpr NodeKind kind = NodeKind::NullLiteral;
};

template <> struct NodeTraits<ArrayLiteralNode> {
  static constexpr NodeKind kind = NodeKind::ArrayLiteral;
};

template <> struct NodeTraits<ObjectLiteralNode> {
  static constexpr NodeKind kind = NodeKind::ObjectLiteral;
};

template <> struct NodeTraits<ObjectFieldNode> {
  static constexpr NodeKind kind = NodeKind::ObjectField;
};

// =====================
// Statements
// =====================

template <> struct NodeTraits<BlockStatement> {
  static constexpr NodeKind kind = NodeKind::BlockStatement;
};

template <> struct NodeTraits<IfStatement> {
  static constexpr NodeKind kind = NodeKind::IfStatement;
};

template <> struct NodeTraits<WhileStatement> {
  static constexpr NodeKind kind = NodeKind::WhileStatement;
};

template <> struct NodeTraits<ReturnStatement> {
  static constexpr NodeKind kind = NodeKind::ReturnStatement;
};

template <> struct NodeTraits<ExpressionStatement> {
  static constexpr NodeKind kind = NodeKind::ExpressionStatement;
};

template <> struct NodeTraits<ImportDeclaration> {
  static constexpr NodeKind kind = NodeKind::ImportDeclaration;
};

// =====================
// Names
// =====================

template <> struct NodeTraits<IdentifierNode> {
  static constexpr NodeKind kind = NodeKind::Identifier;
};

template <> struct NodeTraits<QualifiedNameNode> {
  static constexpr NodeKind kind = NodeKind::QualifiedName;
};

// =====================
// Other
// =====================

template <> struct NodeTraits<TypeNode> {
  static constexpr NodeKind kind = NodeKind::Type;
};

template <> struct NodeTraits<PatternNode> {
  static constexpr NodeKind kind = NodeKind::Pattern;
};

template<>
struct NodeTraits<IdentifierPatternNode> {
    static constexpr NodeKind kind = NodeKind::IdentifierPattern;
};

} // namespace celestia::ast
