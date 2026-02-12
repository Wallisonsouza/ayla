#pragma once

#include "ast/ExpressionNode.hpp"
#include "ast/StatementNode.hpp"

namespace ayla::ast::node {

struct IfStatementNode : StatementNode {
  ExpressionNode *condition;
  StatementNode *then_block;
  StatementNode *else_block;

  IfStatementNode(ExpressionNode *cond, StatementNode *then_b, StatementNode *else_b = nullptr) : StatementNode(NodeKind::IfStatement), condition(cond), then_block(then_b), else_block(else_b) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};
} // namespace ayla::ast::node
