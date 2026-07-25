#pragma once
#include "ast/names/IdentifierNode.hpp"
#include "ast/AstNode.hpp"

#include "semantic/symbols/SymbolId.hpp"

namespace ayla::ast {

struct TypeNode : AstNode {
  IdentifierNode *name;
  SymbolId symbol_id;
  std::vector<TypeNode *> generics;
  bool is_primitive = false;

  TypeNode(IdentifierNode *n, bool primitive = false) : AstNode(NodeKind::Type), name(n), is_primitive(primitive) {}

  TypeNode(IdentifierNode *n, std::vector<TypeNode *> g) : AstNode(NodeKind::Type), name(n), generics(std::move(g)) {}
};

} // namespace ayla::ast