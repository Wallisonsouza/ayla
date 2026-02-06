#pragma once

#include "frontend/ast/ExpressionNode.hpp"
#include "frontend/ast/expressions/IdentifierExpressionNode.hpp"

namespace ayla::ast::node {

struct MemberAccessExpressionNode : ExpressionNode {
  ExpressionNode *base;
  IdentifierExpressionNode *field;

  MemberAccessExpressionNode(ExpressionNode *b, IdentifierExpressionNode *f) : ExpressionNode(NodeKind::MemberAccess), base(b), field(f) {}
  
  void accept(AstVisitor &v) override { v.visit(this); }
  
};

} // namespace ayla::ast::node