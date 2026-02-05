#pragma once

#include "frontend/ast/ExpressionNode.hpp"
#include "frontend/ast/StatementNode.hpp"

namespace ayla::ast::node {

struct IfStatementNode : StatementNode {
  ExpressionNode *condition;
  StatementNode *then_block;
  StatementNode *else_block;

  IfStatementNode(ExpressionNode *cond, StatementNode *then_b, StatementNode *else_b = nullptr) : StatementNode(NodeKind::IfStatement), condition(cond), then_block(then_b), else_block(else_b) {}
};
} // namespace ayla::ast::node
