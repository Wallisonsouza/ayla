#pragma once
#include "core/node/BinaryOp.hpp"
#include "frontend/ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct BinaryExpressionNode : ExpressionNode {

  ExpressionNode *lhs;
  BinaryOperation op;
  ExpressionNode *rhs;

  BinaryExpressionNode(ExpressionNode *l, BinaryOperation o, ExpressionNode *r) : ExpressionNode(NodeKind::BinaryExpression), lhs(l), op(o), rhs(r) {}
};

} // namespace ayla::ast::node