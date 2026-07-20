#pragma once


#include "ast/TypeNode.hpp"

#include "ast/names/QualifiedNameNode.hpp"
#include "semantic/symbols/SymbolId.hpp"

namespace ayla::ast {

struct PatternNode : AstNode {
  using AstNode::AstNode;
};

struct IdentifierPatternNode : PatternNode {
  NameNode *name;
  SymbolId symbol_id;
  TypeNode *type_annotation;

  IdentifierPatternNode(NameNode *n, TypeNode *type = nullptr) : PatternNode(NodeKind::IdentifierPattern), name(n), type_annotation(type) {}

  
};

} // namespace ayla::ast