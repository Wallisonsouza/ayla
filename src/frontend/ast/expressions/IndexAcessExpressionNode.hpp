#pragma once

#include "frontend/ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct IndexAccessNode : ExpressionNode {
  ExpressionNode *base;
  ExpressionNode *index;

  IndexAccessNode(ExpressionNode *b, ExpressionNode *i) : ExpressionNode(NodeKind::IndexAccess), base(b), index(i) {}
};

} // namespace ayla::ast::node