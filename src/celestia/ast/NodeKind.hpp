#pragma once

namespace celestia::ast {

enum class NodeKind {
  // === Base ===
  Unknown,
  NumberLiteral,
  StringLiteral,
  BooleanLiteral,
  ObjectLiteral,
  StructLiteral,
  StructFieldInitializer,
  ObjectField,
  ObjectFieldList,
  CharLiteral,
  NullLiteral,
  Name,
  Interface,
  NamePattern,
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
  ImportDeclaration,
  StructDeclaration,
  FieldDeclaration,

  // === Declarations ===
  VariableDeclaration,
  FunctionDeclaration,
  OperatorDeclaration,
  ModuleDeclaration,
  CapabilityDeclaration,
  ImplementationDeclaration,

  Call,
  FunctionParameter,
  NativeFunctionDeclaration,
  TypeDeclaration,
  ParameterDeclaration,

  IdentifierExpression,
  Identifier,
  CallExpression,
  BinaryExpression,
  UnaryExpression,
  LiteralExpression,
  AssignmentExpression,

  // === Types ===
  Type,
  ArrayType,
  NamedType,
  ReferenceType,
  TypeReference,
  GenericType,
  GenericIdentifier,
  GenericParameter,

  Assignment,
  Pattern,
  Error,
  ParameterList,
  ArrayLiteral
};

} // namespace celestia::ast
