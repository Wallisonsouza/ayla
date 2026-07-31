#pragma once

#include "celestia/ast/StatementNode.hpp"

namespace celestia::ast {
struct DeclarationNode : StatementNode {
  bool resolved = false;
  explicit DeclarationNode(NodeKind k) : StatementNode(k) {}
};
} // namespace celestia::ast