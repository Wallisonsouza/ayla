#pragma once

#include "ast/ExpressionNode.hpp"
#include "ast/StatementNode.hpp"

namespace ayla::ast::node {

struct ExpressionStatementNode : StatementNode {
  ExpressionNode *expression;

  explicit ExpressionStatementNode(ExpressionNode *expr) : StatementNode(NodeKind::ExpressionStatement), expression(expr) {}

  
};

} // namespace ayla::ast::node
