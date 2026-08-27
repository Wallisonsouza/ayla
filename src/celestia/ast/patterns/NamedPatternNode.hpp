#pragma once

#include "celestia/ast/types/TypeNode.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"
#include "PatternNode.hpp"

namespace celestia::ast {

struct NamedPattern : PatternNode {
  IdentifierNode *name;
  TypeNode *type_annotation;

  NamedPattern(IdentifierNode *n, TypeNode *type = nullptr) : PatternNode(NodeKind::NamedPattern), name(n), type_annotation(type) {}
};

} // namespace celestia::ast