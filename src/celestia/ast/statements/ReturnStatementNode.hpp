#pragma once

#include "celestia/ast/ExpressionNode.hpp"
#include "celestia/ast/StatementNode.hpp"

namespace celestia::ast::node {
struct ReturnStatementNode : StatementNode {
  ExpressionNode *value = nullptr;

  ReturnStatementNode(ExpressionNode *v) : StatementNode(NodeKind::ReturnStatement), value(v) {}

  
};
} // namespace celestia::ast::node
