#pragma once

#include "celestia/ast/ExpressionNode.hpp"
#include "celestia/ast/StatementNode.hpp"

namespace celestia::ast::node {

struct WhileStatementNode : StatementNode {
  ExpressionNode *condition;
  StatementNode *body;

  WhileStatementNode(ExpressionNode *cond, StatementNode *block) : StatementNode(NodeKind::WhileStatement), condition(cond), body(block) {}
};

} // namespace celestia::ast::node
