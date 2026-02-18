#pragma once

#include "ast/ExpressionNode.hpp"

namespace ayla::ast::node {

struct CallExpressionNode : ExpressionNode {
  ExpressionNode *callee;
  std::vector<ExpressionNode *> arguments;

  CallExpressionNode(ExpressionNode *c, std::vector<ExpressionNode *> a) : ExpressionNode(NodeKind::CallExpression), callee(c), arguments(std::move(a)) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node