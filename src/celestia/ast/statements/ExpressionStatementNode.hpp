#pragma once

#include "celestia/ast/ExpressionNode.hpp"
#include "celestia/ast/StatementNode.hpp"

namespace celestia::ast::node {

struct ExpressionStatementNode : StatementNode {
  ExpressionNode *expression;

  explicit ExpressionStatementNode(ExpressionNode *expr) : StatementNode(NodeKind::ExpressionStatement), expression(expr) {}

  
};

} // namespace celestia::ast::node
