#pragma once

#include "celestia/ast/TypeNode.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"

namespace celestia::ast {

struct PatternNode : AstNode {
  using AstNode::AstNode;
};

struct IdentifierPatternNode : PatternNode {
  IdentifierNode *name;
  SymbolId symbol_id;
  TypeNode *type_annotation;

  IdentifierPatternNode(IdentifierNode *n, TypeNode *type = nullptr) : PatternNode(NodeKind::IdentifierPattern), name(n), type_annotation(type) {}
};

} // namespace celestia::ast