
#pragma once

#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"

namespace celestia::ast {

struct IdentifierExpressionNode : Expression {

  IdentifierNode *name;
  explicit IdentifierExpressionNode(IdentifierNode *n) : Expression(NodeKind::IdentifierExpression), name(n){}

  
};
} // namespace celestia::ast*