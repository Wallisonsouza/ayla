#pragma once

#include "ast/AstNode.hpp"
#include "ast/TypeNode.hpp"
#include "ast/expressions/IdentifierExpressionNode.hpp"
#include "semantic/symbols/SymbolId.hpp"
#include <cstdint>

namespace ayla::ast {

struct PatternNode : AstNode {
  using AstNode::AstNode;
};

struct IdentifierPatternNode : PatternNode {
  node::IdentifierExpressionNode *identifier;
  SymbolId symbol_id;
  TypeNode *type_annotation;
  uint32_t local_slot;

  IdentifierPatternNode(node::IdentifierExpressionNode *identifier, TypeNode *type = nullptr) : PatternNode(NodeKind::IdentifierPattern), identifier(identifier), type_annotation(type) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast