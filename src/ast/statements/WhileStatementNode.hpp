#pragma once

#include "ast/ExpressionNode.hpp"
#include "ast/StatementNode.hpp"

namespace ayla::ast::node {

struct WhileStatementNode : StatementNode {
  ExpressionNode *condition;
  StatementNode *body;

  WhileStatementNode(ExpressionNode *cond, StatementNode *block) : StatementNode(NodeKind::WhileStatement), condition(cond), body(block) {}

  
};

} // namespace ayla::ast::node
