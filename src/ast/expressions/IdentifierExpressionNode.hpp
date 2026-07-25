
#pragma once

#include "ast/ExpressionNode.hpp"
#include "ast/names/QualifiedNameNode.hpp"

namespace ayla::ast::node {

struct IdentifierExpressionNode : ExpressionNode {

  IdentifierNode *name;
  explicit IdentifierExpressionNode(IdentifierNode *n) : ExpressionNode(NodeKind::IdentifierExpression), name(n){}

  
};
} // namespace ayla::ast::node*