#pragma once

#include "ast/StatementNode.hpp"

namespace ayla::ast {
struct DeclarationNode : StatementNode {
  bool resolved = false;
  explicit DeclarationNode(NodeKind k) : StatementNode(k) {}
};
} // namespace ayla::ast