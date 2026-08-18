#pragma once

#include "NodeKind.hpp"
#include <string_view>

namespace celestia::ast {

constexpr std::string_view node_kind_name(NodeKind kind) {

  switch (kind) {

  case NodeKind::Unknown: return "Unknown";

  case NodeKind::NumberLiteral: return "NumberLiteral";
  case NodeKind::StringLiteral: return "StringLiteral";
  case NodeKind::BooleanLiteral: return "BooleanLiteral";
  case NodeKind::ObjectLiteral: return "ObjectLiteral";
  case NodeKind::StructLiteral: return "StructLiteral";
  case NodeKind::StructFieldInitializer: return "StructFieldInitializer";
  case NodeKind::ObjectField: return "ObjectField";
  case NodeKind::ObjectFieldList: return "ObjectFieldList";
  case NodeKind::CharLiteral: return "CharLiteral";
  case NodeKind::NullLiteral: return "NullLiteral";

  case NodeKind::Name: return "Name";
  case NodeKind::Identifier: return "Identifier";
  case NodeKind::QualifiedName: return "QualifiedName";

  case NodeKind::Interface: return "Interface";
  case NodeKind::NamePattern: return "NamePattern";

  case NodeKind::MemberAccess: return "MemberAccess";
  case NodeKind::IndexAccess: return "IndexAccess";
  case NodeKind::BlockStatement: return "BlockStatement";
  case NodeKind::IfStatement: return "IfStatement";
  case NodeKind::WhileStatement: return "WhileStatement";
  case NodeKind::ForStatement: return "ForStatement";
  case NodeKind::ReturnStatement: return "ReturnStatement";
  case NodeKind::ExpressionStatement: return "ExpressionStatement";

  case NodeKind::ImportDeclaration: return "ImportDeclaration";
  case NodeKind::StructDeclaration: return "StructDeclaration";
  case NodeKind::FieldDeclaration: return "FieldDeclaration";

  case NodeKind::VariableDeclaration: return "VariableDeclaration";
  case NodeKind::FunctionDeclaration: return "FunctionDeclaration";
  case NodeKind::OperatorDeclaration: return "OperatorDeclaration";
  case NodeKind::ModuleDeclaration: return "ModuleDeclaration";
  case NodeKind::CapabilityDeclaration: return "CapabilityDeclaration";
  case NodeKind::ImplementationDeclaration: return "ImplementationDeclaration";

  case NodeKind::Call: return "Call";
  case NodeKind::FunctionParameter: return "FunctionParameter";
  case NodeKind::NativeFunctionDeclaration: return "NativeFunctionDeclaration";
  case NodeKind::TypeDeclaration: return "TypeDeclaration";
  case NodeKind::ParameterDeclaration: return "ParameterDeclaration";

  case NodeKind::IdentifierExpression: return "IdentifierExpression";
  case NodeKind::CallExpression: return "CallExpression";
  case NodeKind::BinaryExpression: return "BinaryExpression";
  case NodeKind::UnaryExpression: return "UnaryExpression";
  case NodeKind::LiteralExpression: return "LiteralExpression";
  case NodeKind::AssignmentExpression: return "AssignmentExpression";

  case NodeKind::Type: return "Type";
  case NodeKind::ArrayType: return "ArrayType";
  case NodeKind::NamedType: return "NamedType";
  case NodeKind::ReferenceType: return "ReferenceType";
  case NodeKind::TypeReference: return "TypeReference";
  case NodeKind::GenericType: return "GenericType";
  case NodeKind::GenericIdentifier: return "GenericIdentifier";
  case NodeKind::GenericParameter: return "GenericParameter";

  case NodeKind::Assignment: return "Assignment";
  case NodeKind::Pattern: return "Pattern";
  case NodeKind::Error: return "Error";
  case NodeKind::ParameterList: return "ParameterList";
  case NodeKind::ArrayLiteral: return "ArrayLiteral";
  }

  return "Unknown";
}

} // namespace celestia::ast