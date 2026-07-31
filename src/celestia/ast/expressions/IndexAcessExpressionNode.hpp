#pragma once

#include "celestia/ast/ExpressionNode.hpp"

namespace celestia::ast::node {

struct IndexAccessExpressionNode : ExpressionNode {
  
  ExpressionNode *base;
  ExpressionNode *index;

  IndexAccessExpressionNode(ExpressionNode *b, ExpressionNode *i) : ExpressionNode(NodeKind::IndexAccess), base(b), index(i) {}

  
};

} // namespace celestia::ast::node