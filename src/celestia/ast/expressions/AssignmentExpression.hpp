#pragma once

#include "celestia/ast/ExpressionNode.hpp"

namespace celestia::ast::node {

struct AssignmentExpressionNode : ExpressionNode {
  ExpressionNode *target;
  ExpressionNode *value;

  AssignmentExpressionNode(ExpressionNode *t, ExpressionNode *v) : ExpressionNode(NodeKind::Assignment), target(t), value(v) {}

  
};
} // namespace celestia::ast::node
