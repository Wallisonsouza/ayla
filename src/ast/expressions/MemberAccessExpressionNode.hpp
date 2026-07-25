#pragma once

#include "ast/ExpressionNode.hpp"
#include "ast/names/QualifiedNameNode.hpp"

namespace ayla::ast::node {

struct MemberAccessExpressionNode : ExpressionNode {
  ExpressionNode *base;
  IdentifierNode *member;

  MemberAccessExpressionNode(ExpressionNode *b, IdentifierNode *f) : ExpressionNode(NodeKind::MemberAccess), base(b), member(f) {}

  
};

} // namespace ayla::ast::node