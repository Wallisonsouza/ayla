#pragma once

#include "ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct IndexAccessExpressionNode : ExpressionNode {
  ExpressionNode *base;
  ExpressionNode *index;

  IndexAccessExpressionNode(ExpressionNode *b, ExpressionNode *i) : ExpressionNode(NodeKind::IndexAccess), base(b), index(i) {}

  
};

} // namespace ayla::ast::node