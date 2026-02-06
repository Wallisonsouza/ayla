#pragma once

#include "frontend/ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct AssignmentExpressionNode : ExpressionNode {
  ExpressionNode *target;
  ExpressionNode *value;

  AssignmentExpressionNode(ExpressionNode *t, ExpressionNode *v) : ExpressionNode(NodeKind::Assignment), target(t), value(v) {}
  
  void accept(AstVisitor &v) override { v.visit(this); }
  
};
} // namespace ayla::ast::node