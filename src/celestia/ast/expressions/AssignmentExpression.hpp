#pragma once

#include "celestia/ast/expressions/ExpressionNode.hpp"

namespace celestia::ast {

struct AssignmentExpressionNode : Expression {
  Expression *target;
  Expression *value;

  AssignmentExpressionNode(Expression *t, Expression *v) : Expression(NodeKind::Assignment), target(t), value(v) {}

  
};
} // namespace celestia::ast
