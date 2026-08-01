#pragma once

#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/core/operators/UnaryOperation.hpp"

namespace celestia::ast {

struct UnaryExpressionNode : Expression {

  UnaryOperation op;
  Expression *operand;

  UnaryExpressionNode(UnaryOperation op, Expression *operand) : Expression(NodeKind::UnaryExpression), operand(operand), op(op) {}

  
};

} // namespace celestia::ast