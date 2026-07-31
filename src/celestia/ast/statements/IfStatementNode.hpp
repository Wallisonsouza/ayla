#pragma once

#include "celestia/ast/ExpressionNode.hpp"
#include "celestia/ast/StatementNode.hpp"

namespace celestia::ast::node {

struct IfStatementNode : StatementNode {
  ExpressionNode *condition;
  StatementNode *then_block;
  StatementNode *else_block;

  IfStatementNode(ExpressionNode *cond, StatementNode *then_b, StatementNode *else_b = nullptr) : StatementNode(NodeKind::IfStatement), condition(cond), then_block(then_b), else_block(else_b) {}
 
};
} // namespace celestia::ast::node
