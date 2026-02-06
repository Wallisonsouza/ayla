#pragma once
#include "core/memory/SymbolId.hpp"
#include "frontend/ast/AstNode.hpp"
#include "frontend/ast/expressions/IdentifierExpressionNode.hpp"

#include <vector>

namespace ayla::ast {

struct TypeNode : ayla::ast::AstNode {
  node::IdentifierExpressionNode *identifier;
  const std::vector<TypeNode *> generics;
  bool is_primitive = false;
  SymbolId symbol_id;

  explicit TypeNode(node::IdentifierExpressionNode *id, bool primitive = false) : ayla::ast::AstNode(ayla::ast::NodeKind::Type), identifier(id), is_primitive(primitive) {}

  TypeNode(node::IdentifierExpressionNode *id, std::vector<TypeNode *> g) : ayla::ast::AstNode(ayla::ast::NodeKind::Type), identifier(id), generics(std::move(g)) {}

  static bool is_same_type(TypeNode *a, TypeNode *b) {
    if (a->is_primitive && b->is_primitive) { return a->identifier->name == b->identifier->name; }

    if (a->identifier->name != b->identifier->name) return false;
    if (a->generics.size() != b->generics.size()) return false;
    for (size_t i = 0; i < a->generics.size(); i++) {
      if (!is_same_type(a->generics[i], b->generics[i])) return false;
    }
    return true;
  }
};

struct PatternNode : AstNode {
  using AstNode::AstNode;
};

struct IdentifierPatternNode : PatternNode {
  node::IdentifierExpressionNode *identifier;
  SymbolId symbol_id;
  TypeNode *type_annotation;

  IdentifierPatternNode(node::IdentifierExpressionNode *identifier, TypeNode *type = nullptr) : PatternNode(NodeKind::IdentifierPattern), identifier(identifier), type_annotation(type) {}
};

} // namespace ayla::ast