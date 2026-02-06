#pragma once

#include "core/memory/SymbolId.hpp"
#include "frontend/ast/AstNode.hpp"
#include "frontend/ast/TypeNode.hpp"
#include "frontend/ast/expressions/IdentifierExpressionNode.hpp"

namespace ayla::ast {

struct PatternNode : AstNode {
  using AstNode::AstNode;
};

struct IdentifierPatternNode : PatternNode {
  node::IdentifierExpressionNode *identifier;
  SymbolId symbol_id;
  TypeNode *type_annotation;

  IdentifierPatternNode(node::IdentifierExpressionNode *identifier, TypeNode *type = nullptr) : PatternNode(NodeKind::IdentifierPattern), identifier(identifier), type_annotation(type) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast