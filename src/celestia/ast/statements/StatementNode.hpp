#pragma once
#include "celestia/ast/Node.hpp"

namespace celestia::ast {
struct Statement : Node {
  explicit Statement(NodeKind k) : Node(k) {}
};
} // namespace celestia::ast