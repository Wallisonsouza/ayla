#pragma once

#include "celestia/ast/declarations/DeclarationNode.hpp"
#include "celestia/ast/names/QualifiedNameNode.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"

#include <optional>

namespace celestia::ast {

struct ImportDeclarationNode : Declaration {
  QualifiedNameNode* name;
  std::optional<std::string> alias;
  SymbolId resolved_symbol_id;

  explicit ImportDeclarationNode(QualifiedNameNode* n) : Declaration(NodeKind::ImportDeclaration), name(n) {}

  
};
} // namespace celestia::ast
