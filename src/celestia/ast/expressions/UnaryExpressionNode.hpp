#pragma once

#include "celestia/ast/ExpressionNode.hpp"
#include "celestia/core/operators/UnaryOperation.hpp"

namespace celestia::ast::node {

struct UnaryExpressionNode : ExpressionNode {

  UnaryOperation op;
  ExpressionNode *operand;

  UnaryExpressionNode(UnaryOperation op, ExpressionNode *operand) : ExpressionNode(NodeKind::UnaryExpression), operand(operand), op(op) {}

  
};

} // namespace celestia::ast::node