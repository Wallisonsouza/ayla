#pragma once

namespace ayla::ast {

enum class NodeKind {
  // === Base ===
  Unknown,
  NumberLiteral,
  StringLiteral,
  BooleanLiteral,
  ObjectLiteral,
  ObjectField,
  ObjectFieldList,
  CharLiteral,
  NullLiteral,
  IdentifierExpression,
  Interface,
  IdentifierPattern,

  // === Statements ===

  IndexAccessExpression,
  BlockStatement,
  IfStatement,
  WhileStatement,
  ForStatement,
  ReturnStatement,
  ExpressionStatement,
  ImportStatement,

  // === Declarations ===
  VariableDeclaration,
  FunctionDeclaration,
  OperatorDeclaration,
  ModuleDeclaration,

  FunctionParameter,
  NativeFunctionDeclaration,
  TypeDeclaration,
  ParameterDeclaration,

  MemberAccessExpression,
  CallExpression,
  BinaryExpression,
  UnaryExpression,
  LiteralExpression,

  // === Types ===
  Type,
  TypeReference,
  GenericType,
  AssignmentExpression,
  Pattern,
  Error,
  ParameterList,
  ArrayLiteral
};

} // namespace ayla::ast
