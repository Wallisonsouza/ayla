#include "frontend/ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct NumberLiteralNode : ExpressionNode {
  double value;

  explicit NumberLiteralNode(double v) : ExpressionNode(NodeKind::NumberLiteral), value(v) {}
};

struct StringLiteralNode : ExpressionNode {
  std::string value;

  explicit StringLiteralNode(std::string v) : ExpressionNode(NodeKind::StringLiteral), value(std::move(v)) {}
};

struct BoolLiteralNode : ExpressionNode {
  bool value;

  explicit BoolLiteralNode(bool v) : ExpressionNode(NodeKind::BooleanLiteral), value(v) {}
};

struct NullLiteralNode : ExpressionNode {
  NullLiteralNode() : ExpressionNode(NodeKind::NullLiteral) {}
};

} // namespace ayla::ast::node