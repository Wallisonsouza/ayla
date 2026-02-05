#pragma once

#include "frontend/ast/ExpressionNode.hpp"
#include "frontend/ast/StatementNode.hpp"

namespace ayla::ast::node {

struct WhileStatementNode : StatementNode {
  ExpressionNode *condition;
  StatementNode *body;

  WhileStatementNode(ExpressionNode *cond, StatementNode *block) : StatementNode(NodeKind::WhileStatement), condition(cond), body(block) {}
};

} // namespace ayla::ast::node
