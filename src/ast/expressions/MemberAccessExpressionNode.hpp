#pragma once

#include "ast/ExpressionNode.hpp"
#include "ast/expressions/IdentifierExpressionNode.hpp"

namespace ayla::ast::node {

struct MemberAccessExpressionNode : ExpressionNode {
  ExpressionNode *base;
  IdentifierExpressionNode *field;

  MemberAccessExpressionNode(ExpressionNode *b, IdentifierExpressionNode *f) : ExpressionNode(NodeKind::MemberAccess), base(b), field(f) {}

  
};

} // namespace ayla::ast::node