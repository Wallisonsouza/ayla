#pragma once

#include "ayla/syntax/ast/ExpressionNode.hpp"
#include "ayla/syntax/ast/StatementNode.hpp"

namespace ayla::ast::node {

struct WhileStatementNode : StatementNode {
  ExpressionNode *condition;
  StatementNode *body;

  WhileStatementNode(ExpressionNode *cond, StatementNode *block) : StatementNode(NodeKind::WhileStatement), condition(cond), body(block) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node
