#pragma once

#include "celestia/ast/statements/StatementNode.hpp"
#include <vector>

namespace celestia::ast {

struct BlockStatement : Statement {
  std::vector<Statement *> statements;

  explicit BlockStatement(std::vector<Statement *> stmts = {}) : Statement(NodeKind::BlockStatement), statements(std::move(stmts)) {}
};
} // namespace celestia::ast
