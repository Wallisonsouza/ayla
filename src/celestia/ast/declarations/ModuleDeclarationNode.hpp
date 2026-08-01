#pragma once
#include "celestia/ast/declarations/DeclarationNode.hpp"
#include "celestia/ast/names/QualifiedNameNode.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"

namespace celestia::ast {

struct ModuleDeclaration : Declaration {

  QualifiedNameNode *name;

  std::vector<Declaration *> declarations;
  SymbolId resolved_symbol_id;

  ModuleDeclaration(QualifiedNameNode *n, std::vector<Declaration *> decls = {}) : Declaration(NodeKind::ModuleDeclaration), name(n), declarations(std::move(decls)) {}
};

} // namespace celestia::ast
