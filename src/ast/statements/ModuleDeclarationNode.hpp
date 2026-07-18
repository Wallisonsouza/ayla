#pragma once
#include "ast/expressions/IdentifierExpressionNode.hpp"

namespace ayla::ast::node {

struct ModuleDeclarationNode : StatementNode {
  std::vector<IdentifierExpressionNode *> path;
  std::vector<AstNode *> body;
  SymbolId resolved_symbol_id;

  ModuleDeclarationNode(std::vector<IdentifierExpressionNode *> p, std::vector<AstNode *> b) : StatementNode(NodeKind::ModuleDeclaration), path(std::move(p)), body(std::move(b)) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node
