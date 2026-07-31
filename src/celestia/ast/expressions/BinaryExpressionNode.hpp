#pragma once
#include "celestia/ast/ExpressionNode.hpp"
#include "celestia/core/operators/BinaryOperation.hpp"

namespace celestia::ast::node {

struct BinaryExpressionNode : ExpressionNode {

  ExpressionNode *lhs;
  BinaryOperation op;
  ExpressionNode *rhs;

  BinaryExpressionNode(ExpressionNode *l, BinaryOperation o, ExpressionNode *r) : ExpressionNode(NodeKind::BinaryExpression), lhs(l), op(o), rhs(r) {}

  
};

} // namespace celestia::ast::node