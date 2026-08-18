#pragma once

#include "celestia/ast/types/TypeNode.hpp"

namespace celestia::ast {

struct ArrayType : TypeNode {

  TypeNode *element_type;

  explicit ArrayType(TypeNode *element_type) : TypeNode(NodeKind::ArrayType), element_type(element_type) {}
};
} // namespace celestia::ast