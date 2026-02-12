#pragma once

#include "ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct IndexAccessNode : ExpressionNode {
  ExpressionNode *base;
  ExpressionNode *index;

  IndexAccessNode(ExpressionNode *b, ExpressionNode *i) : ExpressionNode(NodeKind::IndexAccess), base(b), index(i) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node