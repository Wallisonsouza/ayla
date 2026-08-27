#pragma once

#include "celestia/ast/Node.hpp"

namespace celestia::ast {

struct TypeNode : Node {
  explicit TypeNode(NodeKind kind) : Node(kind) {}
};

} // namespace celestia::ast