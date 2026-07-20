#include "ast/AstNode.hpp"
#include "ast/names/QualifiedNameNode.hpp"
#include "semantic/symbols/SymbolId.hpp"

namespace ayla::ast {

struct TypeNode : AstNode {
  NameNode *name;
  SymbolId symbol_id;
  std::vector<TypeNode *> generics;
  bool is_primitive = false;

  TypeNode(NameNode *n, bool primitive = false) : AstNode(NodeKind::Type), name(n), is_primitive(primitive) {}

  TypeNode(NameNode *n, std::vector<TypeNode *> g) : AstNode(NodeKind::Type), name(n), generics(std::move(g)) {}
};

} // namespace ayla::ast