#pragma once

#include "celestia/ast/statements/StatementNode.hpp"

namespace celestia::ast {
struct Declaration : Statement {
  bool resolved = false;
  explicit Declaration(NodeKind k) : Statement(k) {}
};
} // namespace celestia::ast