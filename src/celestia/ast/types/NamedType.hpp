#pragma once

#include "celestia/ast/types/TypeNode.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"

namespace celestia::ast {

struct NamedType : TypeNode {

  IdentifierNode *name;
  bool is_primitive;

  NamedType(IdentifierNode *name, bool primitive = false) : TypeNode(NodeKind::NamedType), name(name), is_primitive(primitive) {}
};
} // namespace celestia::ast