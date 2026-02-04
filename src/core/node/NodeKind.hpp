#pragma once

namespace core::ast {

enum class NodeKindBase { Internal, Expression, Statement, Type, Pattern, Unknown };

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
  PathExpression,
  Interface,

  // === Statements ===
  MemberAccess,
  IndexAccess,
  BlockStatement,
  IfStatement,
  WhileStatement,
  ForStatement,
  ReturnStatement,
  ExpressionStatement,
  Import,

  // === Declarations ===
  VariableDeclaration,
  FunctionDeclaration,
  OperatorDeclaration,
  ModuleDeclaration,

  FunctionCall,
  FunctionParameter,
  NativeFunctionDeclaration,
  TypeDeclaration,
  ParameterDeclaration,

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

} // namespace core::ast
