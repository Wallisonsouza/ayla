#pragma once
#include "core/node/BinaryOp.hpp"
#include "core/node/Type.hpp"

namespace parser::node {

struct BinaryExpressionNode : ayla::ast::ExpressionNode {

  ayla::ast::ExpressionNode *lhs;
  ayla::ast::BinaryOperation op;
  ayla::ast::ExpressionNode *rhs;

  BinaryExpressionNode(ayla::ast::ExpressionNode *l, ayla::ast::BinaryOperation o, ayla::ast::ExpressionNode *r) : ExpressionNode(ayla::ast::NodeKind::BinaryExpression), lhs(l), op(o), rhs(r) {}
};

} // namespace parser::node
