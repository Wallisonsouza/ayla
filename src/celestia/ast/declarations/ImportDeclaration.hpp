#pragma once

#include "Declaration.hpp"
#include "celestia/ast/names/QualifiedNameNode.hpp"

#include <optional>

namespace celestia::ast {

struct ImportDeclaration : Declaration {
  QualifiedNameNode* name;
  std::optional<std::string> alias;
  SymbolId resolved_symbol_id;

  explicit ImportDeclaration(QualifiedNameNode* n) : Declaration(NodeKind::ImportDeclaration), name(n) {}


};
} // namespace celestia::ast
