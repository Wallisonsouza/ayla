#pragma once

#include "celestia/ast/ExpressionNode.hpp"

namespace celestia::ast::node {

struct CallExpressionNode : ExpressionNode {
  ExpressionNode *callee;
  std::vector<ExpressionNode *> arguments;

  CallExpressionNode(ExpressionNode *c, std::vector<ExpressionNode *> a) : ExpressionNode(NodeKind::Call), callee(c), arguments(std::move(a)) {}

  
};

} // namespace celestia::ast::node