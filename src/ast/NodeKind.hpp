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
  Name,
  Interface,
  IdentifierPattern,
  QualifiedName,

  // === Statements ===
  MemberAccess,
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

  Call,
  FunctionParameter,
  NativeFunctionDeclaration,
  TypeDeclaration,
  ParameterDeclaration,

  IdentifierExpression,
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
