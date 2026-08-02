#pragma once

#include "celestia/ast/Node.hpp"
#include "celestia/ast/NodeKind.hpp"

namespace celestia::ast {

struct PatternNode : Node {
  explicit PatternNode(NodeKind kind = NodeKind::Pattern) : Node(kind) {}
};

} // namespace celestia::ast