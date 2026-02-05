#pragma once
#include "core/module/module.hpp"
#include "core/node/Type.hpp"

namespace ayla::ast::node {

struct ModuleDeclarationNode : StatementNode {
  std::vector<IdentifierNode *> path;
  std::vector<AstNode *> body;
  ModuleId resolved_module_id;
  SymbolId resolved_symbol_id;

  ModuleDeclarationNode(std::vector<IdentifierNode *> p, std::vector<AstNode *> b) : StatementNode(NodeKind::ModuleDeclaration), path(std::move(p)), body(std::move(b)) {}
};

} // namespace ayla::ast::node
