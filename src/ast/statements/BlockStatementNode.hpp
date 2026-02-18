#pragma once

#include "ast/StatementNode.hpp"
#include <vector>

namespace ayla::ast::node {

struct BlockStatementNode : StatementNode {
  const std::vector<StatementNode *> statements;

  explicit BlockStatementNode(std::vector<StatementNode *> stmts = {}) : StatementNode(NodeKind::BlockStatement), statements(std::move(stmts)) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};
} // namespace ayla::ast::node
