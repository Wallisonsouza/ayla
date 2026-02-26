#pragma once

#include "ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct IndexAccessExpressionNode : ExpressionNode {
  ExpressionNode *base;
  ExpressionNode *index;

  IndexAccessExpressionNode(ExpressionNode *b, ExpressionNode *i) : ExpressionNode(NodeKind::IndexAccessExpression), base(b), index(i) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node