#pragma once

#include "core/node/Type.hpp"
#include "frontend/ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct MemberAccessExpressionNode : ExpressionNode {
  ExpressionNode *base;
  IdentifierNode *field;

  MemberAccessExpressionNode(ExpressionNode *b, IdentifierNode *f) : ExpressionNode(NodeKind::MemberAccess), base(b), field(f) {}
};

} // namespace ayla::ast::node