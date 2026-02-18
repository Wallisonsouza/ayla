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
  Identifier,
  Interface,
  IdentifierPattern,

  // === Statements ===

  IndexAccess,
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
  AssignmentExpression,

  // === Types ===
  Type,
  TypeReference,
  GenericType,
  Assignment,
  Pattern,
  Error,
  ParameterList,
  ArrayLiteral
};

} // namespace ayla::ast
