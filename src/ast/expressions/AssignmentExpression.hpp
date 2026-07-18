#pragma once

#include "ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct AssignmentExpressionNode : ExpressionNode {
  ExpressionNode *target;
  ExpressionNode *value;

  AssignmentExpressionNode(ExpressionNode *t, ExpressionNode *v) : ExpressionNode(NodeKind::Assignment), target(t), value(v) {}

  
};
} // namespace ayla::ast::node
