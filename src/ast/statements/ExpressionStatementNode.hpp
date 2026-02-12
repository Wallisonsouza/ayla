#pragma once

#include "ast/ExpressionNode.hpp"
#include "ast/StatementNode.hpp"

namespace ayla::ast::node {

struct ExpressionStatementNode : StatementNode {
  ExpressionNode *expression;

  explicit ExpressionStatementNode(ExpressionNode *expr) : StatementNode(NodeKind::ExpressionStatement), expression(expr) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node
