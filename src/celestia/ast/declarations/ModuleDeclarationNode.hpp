#pragma once
#include "celestia/ast/declarations/DeclarationNode.hpp"
#include "celestia/ast/names/QualifiedNameNode.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"

namespace celestia::ast::node {

struct ModuleDeclarationNode : DeclarationNode {

  QualifiedNameNode *name;

  std::vector<DeclarationNode *> declarations;
  SymbolId resolved_symbol_id;

  ModuleDeclarationNode(QualifiedNameNode *n, std::vector<DeclarationNode *> decls = {}) : DeclarationNode(NodeKind::ModuleDeclaration), name(n), declarations(std::move(decls)) {}
};

} // namespace celestia::ast::node
