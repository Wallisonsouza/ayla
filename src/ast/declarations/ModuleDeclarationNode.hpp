#pragma once
#include "ast/declarations/DeclarationNode.hpp"
#include "ast/names/QualifiedNameNode.hpp"
#include "semantic/symbols/SymbolId.hpp"

namespace ayla::ast::node {

struct ModuleDeclarationNode : DeclarationNode {
  
  QualifiedNameNode *name;

  std::vector<DeclarationNode *> declarations;
  SymbolId resolved_symbol_id;

  ModuleDeclarationNode(QualifiedNameNode *n, std::vector<DeclarationNode *> decls = {}) : DeclarationNode(NodeKind::ModuleDeclaration), name(n), declarations(std::move(decls)) {}
};

} // namespace ayla::ast::node
