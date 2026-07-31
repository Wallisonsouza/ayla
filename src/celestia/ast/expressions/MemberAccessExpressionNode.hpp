#pragma once

#include "celestia/ast/ExpressionNode.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"

namespace celestia::ast::node {

struct MemberAccessExpressionNode : ExpressionNode {
  ExpressionNode *base;
  IdentifierNode *member;

  MemberAccessExpressionNode(ExpressionNode *b, IdentifierNode *f) : ExpressionNode(NodeKind::MemberAccess), base(b), member(f) {}

  
};

} // namespace celestia::ast::node