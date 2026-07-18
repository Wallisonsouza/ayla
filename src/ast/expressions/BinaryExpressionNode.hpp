#pragma once
#include "ast/ExpressionNode.hpp"
#include "core/operators/BinaryOperation.hpp"

namespace ayla::ast::node {

struct BinaryExpressionNode : ExpressionNode {

  ExpressionNode *lhs;
  BinaryOperation op;
  ExpressionNode *rhs;

  BinaryExpressionNode(ExpressionNode *l, BinaryOperation o, ExpressionNode *r) : ExpressionNode(NodeKind::BinaryExpression), lhs(l), op(o), rhs(r) {}

  
};

} // namespace ayla::ast::node