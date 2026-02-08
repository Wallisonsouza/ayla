#include "frontend/ast/AstNode.hpp"
#include "frontend/symbols/SymbolId.hpp"

namespace ayla::ast {

struct TypeNode : AstNode {
  std::string name;
  SymbolId symbol_id;
  std::vector<TypeNode *> generics;
  bool is_primitive = false;

  TypeNode(std::string name_, bool primitive = false) : AstNode(NodeKind::Type), name(std::move(name_)), is_primitive(primitive) {}

  TypeNode(std::string name_, std::vector<TypeNode *> g) : AstNode(NodeKind::Type), name(std::move(name_)), generics(std::move(g)) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast