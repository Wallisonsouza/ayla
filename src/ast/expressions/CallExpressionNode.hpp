#pragma once

#include "ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct CallExpressionNode : ExpressionNode {
  ExpressionNode *callee;
  std::vector<ExpressionNode *> arguments;

  CallExpressionNode(ExpressionNode *c, std::vector<ExpressionNode *> a) : ExpressionNode(NodeKind::FunctionCall), callee(c), arguments(std::move(a)) {}

  
};

} // namespace ayla::ast::node