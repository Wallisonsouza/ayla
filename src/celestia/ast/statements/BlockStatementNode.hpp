#pragma once

#include "celestia/ast/StatementNode.hpp"
#include <vector>

namespace celestia::ast::node {

struct BlockStatementNode : StatementNode {
  std::vector<StatementNode *> statements;

  explicit BlockStatementNode(std::vector<StatementNode *> stmts = {}) : StatementNode(NodeKind::BlockStatement), statements(std::move(stmts)) {}

  
};
} // namespace celestia::ast::node
