#pragma once

#include "celestia/ast/types/TypeNode.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"
#include "PatternNode.hpp"

namespace celestia::ast {

struct IdentifierPatternNode : PatternNode {
  IdentifierNode *name;
  SymbolId symbol_id;
  TypeNode *type_annotation;

  IdentifierPatternNode(IdentifierNode *n, TypeNode *type = nullptr) : PatternNode(NodeKind::NamePattern), name(n), type_annotation(type) {}
};

} // namespace celestia::ast