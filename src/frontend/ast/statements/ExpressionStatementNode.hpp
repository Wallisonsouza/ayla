#pragma once

#include "frontend/ast/ExpressionNode.hpp"
#include "frontend/ast/StatementNode.hpp"

namespace ayla::ast::node {

struct ExpressionStatementNode : StatementNode {
  ExpressionNode *expression;

  explicit ExpressionStatementNode(ExpressionNode *expr) : StatementNode(NodeKind::ExpressionStatement), expression(expr) {}
};

} // namespace ayla::ast::node
