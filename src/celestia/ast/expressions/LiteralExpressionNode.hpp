#pragma once

#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"
#include "celestia/ast/types/TypeNode.hpp"
#include <string>
#include <vector>

namespace celestia::ast {

struct NumberLiteralNode : Expression {
  double value;

  explicit NumberLiteralNode(double v) : Expression(NodeKind::NumberLiteral), value(v) {}
};

struct StringLiteralNode : Expression {
  std::string value;

  explicit StringLiteralNode(std::string v) : Expression(NodeKind::StringLiteral), value(std::move(v)) {}
};

struct BoolLiteralNode : Expression {
  bool value;

  explicit BoolLiteralNode(bool v) : Expression(NodeKind::BooleanLiteral), value(v) {}
};

struct NullLiteralNode : Expression {
  NullLiteralNode() : Expression(NodeKind::NullLiteral) {}
};

struct ArrayLiteralNode : Expression {
  std::vector<Expression *> elements;
  explicit ArrayLiteralNode(std::vector<Expression *> elems) : Expression(NodeKind::ArrayLiteral), elements(std::move(elems)) {}
};

struct ObjectFieldNode : Node {
  Expression *key;
  Expression *value;

  ObjectFieldNode(Expression *k, Expression *v) : Node(NodeKind::ObjectField), key(k), value(v) {}
};

struct ObjectLiteralNode : Expression {
  std::vector<ObjectFieldNode *> fields;

  explicit ObjectLiteralNode(std::vector<ObjectFieldNode *> f) : Expression(NodeKind::ObjectLiteral), fields(std::move(f)) {}
};

struct StructFieldInitializerNode : Node {

  IdentifierNode *name;
  Expression *value;

  StructFieldInitializerNode(IdentifierNode *name, Expression *value) : Node(NodeKind::StructFieldInitializer), name(name), value(value) {}
};

struct StructLiteralNode : Expression {

  TypeNode *type;

  std::vector<StructFieldInitializerNode *> fields;

  StructLiteralNode(TypeNode *type, std::vector<StructFieldInitializerNode *> fields) : Expression(NodeKind::StructLiteral), type(type), fields(std::move(fields)) {}
};

} // namespace celestia::ast
