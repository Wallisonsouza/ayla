#pragma once

#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"

namespace celestia::ast {

struct MemberAccessExpressionNode : Expression {
  Expression *base;
  IdentifierNode *member;

  MemberAccessExpressionNode(Expression *b, IdentifierNode *f) : Expression(NodeKind::MemberAccess), base(b), member(f) {}

  
};

} // namespace celestia::ast