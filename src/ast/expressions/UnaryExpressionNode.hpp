#pragma once

#include "ast/ExpressionNode.hpp"
#include "core/operators/UnaryOperation.hpp"

namespace ayla::ast::node {

struct UnaryExpressionNode : ExpressionNode {

  UnaryOperation op;
  ExpressionNode *operand;

  UnaryExpressionNode(UnaryOperation op, ExpressionNode *operand) : ExpressionNode(NodeKind::UnaryExpression), operand(operand), op(op) {}

  void accept(AstVisitor &v) override {}
};

} // namespace ayla::ast::node