#pragma once

#include "ast/NodeKind.hpp"

// Declarations
#include "ast/declarations/FunctionDeclarationNode.hpp"
#include "ast/declarations/ModuleDeclarationNode.hpp"
#include "ast/declarations/VariableDeclarationNode.hpp"

// Expressions
#include "ast/expressions/AssignmentExpression.hpp"
#include "ast/expressions/BinaryExpressionNode.hpp"
#include "ast/expressions/CallExpressionNode.hpp"
#include "ast/expressions/IdentifierExpressionNode.hpp"
#include "ast/expressions/IndexAcessExpressionNode.hpp"
#include "ast/expressions/LiteralExpressionNode.hpp"
#include "ast/expressions/MemberAccessExpressionNode.hpp"
#include "ast/expressions/UnaryExpressionNode.hpp"

// Statements
#include "ast/statements/BlockStatementNode.hpp"
#include "ast/statements/ExpressionStatementNode.hpp"
#include "ast/statements/IfStatementNode.hpp"
#include "ast/statements/ImportStatementNode.hpp"
#include "ast/statements/ReturnStatementNode.hpp"
#include "ast/statements/WhileStatementNode.hpp"

// Names
#include "ast/names/IdentifierNode.hpp"
#include "ast/names/QualifiedNameNode.hpp"

// Types
#include "ast/TypeNode.hpp"

// Patterns
#include "ast/patterns/PatternNode.hpp"

namespace ayla::ast {

template <typename T> struct NodeTraits;

// =====================
// Declarations
// =====================

template <> struct NodeTraits<node::FunctionDeclarationNode> {
  static constexpr NodeKind kind = NodeKind::FunctionDeclaration;
};

template <> struct NodeTraits<node::VariableDeclarationNode> {
  static constexpr NodeKind kind = NodeKind::VariableDeclaration;
};

template <> struct NodeTraits<node::ModuleDeclarationNode> {
  static constexpr NodeKind kind = NodeKind::ModuleDeclaration;
};

// =====================
// Expressions
// =====================

template <> struct NodeTraits<node::BinaryExpressionNode> {
  static constexpr NodeKind kind = NodeKind::BinaryExpression;
};

template <> struct NodeTraits<node::UnaryExpressionNode> {
  static constexpr NodeKind kind = NodeKind::UnaryExpression;
};

template <> struct NodeTraits<node::CallExpressionNode> {
  static constexpr NodeKind kind = NodeKind::Call;
};

template <> struct NodeTraits<node::AssignmentExpressionNode> {
  static constexpr NodeKind kind = NodeKind::Assignment;
};

template <> struct NodeTraits<node::MemberAccessExpressionNode> {
  static constexpr NodeKind kind = NodeKind::MemberAccess;
};

template <> struct NodeTraits<node::IndexAccessExpressionNode> {
  static constexpr NodeKind kind = NodeKind::IndexAccess;
};

template <> struct NodeTraits<node::IdentifierExpressionNode> {
  static constexpr NodeKind kind = NodeKind::IdentifierExpression;
};

// =====================
// Literals
// =====================

template <> struct NodeTraits<node::NumberLiteralNode> {
  static constexpr NodeKind kind = NodeKind::NumberLiteral;
};

template <> struct NodeTraits<node::StringLiteralNode> {
  static constexpr NodeKind kind = NodeKind::StringLiteral;
};

template <> struct NodeTraits<node::BoolLiteralNode> {
  static constexpr NodeKind kind = NodeKind::BooleanLiteral;
};

template <> struct NodeTraits<node::NullLiteralNode> {
  static constexpr NodeKind kind = NodeKind::NullLiteral;
};

template <> struct NodeTraits<node::ArrayLiteralNode> {
  static constexpr NodeKind kind = NodeKind::ArrayLiteral;
};

template <> struct NodeTraits<node::ObjectLiteralNode> {
  static constexpr NodeKind kind = NodeKind::ObjectLiteral;
};

template <> struct NodeTraits<node::ObjectFieldNode> {
  static constexpr NodeKind kind = NodeKind::ObjectField;
};

// =====================
// Statements
// =====================

template <> struct NodeTraits<node::BlockStatementNode> {
  static constexpr NodeKind kind = NodeKind::BlockStatement;
};

template <> struct NodeTraits<node::IfStatementNode> {
  static constexpr NodeKind kind = NodeKind::IfStatement;
};

template <> struct NodeTraits<node::WhileStatementNode> {
  static constexpr NodeKind kind = NodeKind::WhileStatement;
};

template <> struct NodeTraits<node::ReturnStatementNode> {
  static constexpr NodeKind kind = NodeKind::ReturnStatement;
};

template <> struct NodeTraits<node::ExpressionStatementNode> {
  static constexpr NodeKind kind = NodeKind::ExpressionStatement;
};

template <> struct NodeTraits<node::ImportDeclarationNode> {
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

} // namespace ayla::ast