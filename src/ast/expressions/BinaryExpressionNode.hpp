#pragma once
#include "ast/ExpressionNode.hpp"
#include "core/node/BinaryOp.hpp"

namespace ayla::ast::node {

struct BinaryExpressionNode : ExpressionNode {

  ExpressionNode *lhs;
  BinaryOperation op;
  ExpressionNode *rhs;

  BinaryExpressionNode(ExpressionNode *l, BinaryOperation o, ExpressionNode *r) : ExpressionNode(NodeKind::BinaryExpression), lhs(l), op(o), rhs(r) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node