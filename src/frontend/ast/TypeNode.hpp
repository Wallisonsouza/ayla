#include "frontend/ast/AstNode.hpp"
#include "frontend/ast/expressions/IdentifierExpressionNode.hpp"
#include "frontend/symbols/SymbolId.hpp"

namespace ayla::ast {

struct TypeNode : AstNode {
  node::IdentifierExpressionNode *identifier;
  const std::vector<TypeNode *> generics;
  bool is_primitive = false;
  SymbolId symbol_id;

  explicit TypeNode(node::IdentifierExpressionNode *id, bool primitive = false) : AstNode(NodeKind::Type), identifier(id), is_primitive(primitive) {}

  TypeNode(node::IdentifierExpressionNode *id, std::vector<TypeNode *> g) : AstNode(NodeKind::Type), identifier(id), generics(std::move(g)) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast