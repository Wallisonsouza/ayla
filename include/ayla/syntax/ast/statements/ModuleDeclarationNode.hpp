#pragma once

#include "ayla/syntax/ast/StatementNode.hpp"
#include "core/module/module.hpp"

namespace ayla::ast::node {

struct ModuleDeclarationNode : StatementNode {
  std::vector<IdentifierExpressionNode *> path;
  std::vector<AstNode *> body;
  ModuleId resolved_module_id;
  SymbolId resolved_symbol_id;

  ModuleDeclarationNode(std::vector<IdentifierExpressionNode *> p, std::vector<AstNode *> b) : StatementNode(NodeKind::ModuleDeclaration), path(std::move(p)), body(std::move(b)) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node
