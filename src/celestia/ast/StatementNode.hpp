#pragma once
#include "celestia/ast/AstNode.hpp"

namespace celestia::ast {
struct StatementNode : AstNode {
  bool resolved = false;
  explicit StatementNode(NodeKind k) : AstNode(k) {}
};
} // namespace celestia::ast