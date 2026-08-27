#pragma once
#include "Declaration.hpp"
#include "celestia/ast/names/QualifiedNameNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/semantic/symbol/SymbolId.hpp"

namespace celestia::ast {

struct ModuleInitDeclaration : Declaration {

  BlockStatement *body = nullptr;

  explicit ModuleInitDeclaration(BlockStatement *body) : Declaration(NodeKind::ModuleInitDeclaration), body(body) {}
};

struct ModuleDeclaration : Declaration {

  QualifiedNameNode *name;

  std::vector<Declaration *> declarations;

  SymbolId resolved_symbol_id;

  ModuleDeclaration(QualifiedNameNode *n, std::vector<Declaration *> decls = {}) : Declaration(NodeKind::ModuleDeclaration), name(n), declarations(std::move(decls)) {}
};

} // namespace celestia::ast
