#pragma once

#include "ayla/syntax/ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct MemberAccessExpressionNode : ExpressionNode {
  ExpressionNode *base;
  IdentifierExpressionNode *field;

  MemberAccessExpressionNode(ExpressionNode *b, IdentifierExpressionNode *f) : ExpressionNode(NodeKind::MemberAccessExpression), base(b), field(f) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node