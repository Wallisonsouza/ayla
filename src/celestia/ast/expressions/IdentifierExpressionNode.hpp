
#pragma once

#include "celestia/ast/ExpressionNode.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"

namespace celestia::ast::node {

struct IdentifierExpressionNode : ExpressionNode {

  IdentifierNode *name;
  explicit IdentifierExpressionNode(IdentifierNode *n) : ExpressionNode(NodeKind::IdentifierExpression), name(n){}

  
};
} // namespace celestia::ast::node*