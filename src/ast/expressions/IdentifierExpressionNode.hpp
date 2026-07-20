
#pragma once

#include "ast/ExpressionNode.hpp"
#include "ast/names/QualifiedNameNode.hpp"

namespace ayla::ast::node {

struct IdentifierExpressionNode : ExpressionNode {

  NameNode *name;
  explicit IdentifierExpressionNode(NameNode *n) : ExpressionNode(NodeKind::IdentifierExpression), name(n){}

  
};
} // namespace ayla::ast::node*