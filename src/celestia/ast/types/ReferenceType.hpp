#pragma once

#include "TypeNode.hpp"

namespace celestia::ast {

struct ReferenceType : TypeNode {

  TypeNode *target;

  explicit ReferenceType(TypeNode *target) : TypeNode(NodeKind::ReferenceType), target(target) {}
};

} // namespace celestia::ast