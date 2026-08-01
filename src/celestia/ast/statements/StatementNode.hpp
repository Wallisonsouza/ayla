#pragma once
#include "celestia/ast/Node.hpp"

namespace celestia::ast {
struct Statement : Node {
  bool resolved = false;
  explicit Statement(NodeKind k) : Node(k) {}
};
} // namespace celestia::ast