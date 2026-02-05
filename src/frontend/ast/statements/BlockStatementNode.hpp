#pragma once

#include "frontend/ast/StatementNode.hpp"

namespace ayla::ast::node {

struct BlockStatementNode : StatementNode {
  std::vector<StatementNode *> statements;

  explicit BlockStatementNode(std::vector<StatementNode *> stmts = {}) : StatementNode(NodeKind::BlockStatement), statements(std::move(stmts)) {}
};
} // namespace ayla::ast::node
