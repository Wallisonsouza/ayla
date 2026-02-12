#pragma once

#include "ast/ExpressionNode.hpp"
#include <string>
#include <vector>

namespace ayla::ast::node {

struct NumberLiteralNode : ExpressionNode {
  double value;

  explicit NumberLiteralNode(double v) : ExpressionNode(NodeKind::NumberLiteral), value(v) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

struct StringLiteralNode : ExpressionNode {
  std::string value;

  explicit StringLiteralNode(std::string v) : ExpressionNode(NodeKind::StringLiteral), value(std::move(v)) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

struct BoolLiteralNode : ExpressionNode {
  bool value;

  explicit BoolLiteralNode(bool v) : ExpressionNode(NodeKind::BooleanLiteral), value(v) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

struct NullLiteralNode : ExpressionNode {
  NullLiteralNode() : ExpressionNode(NodeKind::NullLiteral) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

struct ArrayLiteralNode : ExpressionNode {
  std::vector<ExpressionNode *> elements;

  explicit ArrayLiteralNode(std::vector<ExpressionNode *> elems) : ExpressionNode(NodeKind::ArrayLiteral), elements(std::move(elems)) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

struct ObjectFieldNode : AstNode {
  ExpressionNode *key;
  ExpressionNode *value;

  ObjectFieldNode(ExpressionNode *k, ExpressionNode *v) : AstNode(NodeKind::ObjectField), key(k), value(v) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

struct ObjectLiteralNode : ExpressionNode {
  std::vector<ObjectFieldNode *> fields;

  explicit ObjectLiteralNode(std::vector<ObjectFieldNode *> f) : ExpressionNode(NodeKind::ObjectLiteral), fields(std::move(f)) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node
