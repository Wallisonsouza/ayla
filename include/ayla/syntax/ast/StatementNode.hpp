#pragma once
#include "AstNode.hpp"

namespace ayla::ast {
struct StatementNode : AstNode {
  bool resolved = false;
  explicit StatementNode(NodeKind k) : AstNode(k) {}
};
} // namespace ayla::ast