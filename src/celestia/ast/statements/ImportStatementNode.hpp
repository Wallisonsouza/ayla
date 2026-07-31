#pragma once

#include "celestia/ast/declarations/DeclarationNode.hpp"
#include "celestia/ast/names/QualifiedNameNode.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"

#include <optional>

namespace celestia::ast::node {

struct ImportDeclarationNode : DeclarationNode {
  QualifiedNameNode* name;
  std::optional<std::string> alias;
  SymbolId resolved_symbol_id;

  explicit ImportDeclarationNode(QualifiedNameNode* n) : DeclarationNode(NodeKind::ImportDeclaration), name(n) {}

  
};
} // namespace celestia::ast::node
