#pragma once

#include "celestia/ast/Node.hpp"
#include "celestia/semantic/types/type.hpp"

namespace celestia::ast {

struct Expression : Node {
  const semantic::Type *type = nullptr;
  explicit Expression(NodeKind k) : Node(k) {}
};

} // namespace celestia::ast