#pragma once

#include "ast/ExpressionNode.hpp"
#include "ast/StatementNode.hpp"

namespace ayla::ast::node {
struct ReturnStatementNode : StatementNode {
  ExpressionNode *value = nullptr;

  ReturnStatementNode(ExpressionNode *v) : StatementNode(NodeKind::ReturnStatement), value(v) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};
} // namespace ayla::ast::node
