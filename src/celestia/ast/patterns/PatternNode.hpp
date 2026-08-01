#pragma once

#include "celestia/ast/Node.hpp"
#include "celestia/ast/NodeKind.hpp"
#include "celestia/ast/TypeNode.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"

namespace celestia::ast {

struct PatternNode : Node {
  explicit PatternNode(NodeKind kind = NodeKind::Pattern) : Node(kind) {}
};

struct IdentifierPatternNode : PatternNode {
  IdentifierNode *name;
  SymbolId symbol_id;
  TypeNode *type_annotation;

  IdentifierPatternNode(IdentifierNode *n, TypeNode *type = nullptr) : PatternNode(NodeKind::IdentifierPattern), name(n), type_annotation(type) {}
};

} // namespace celestia::ast