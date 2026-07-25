#pragma once
#include "ast/StatementNode.hpp"
#include "ast/declarations/DeclarationNode.hpp"
#include "ast/names/QualifiedNameNode.hpp"
#include "semantic/symbols/SymbolId.hpp"

#include <optional>

namespace ayla::ast::node {

struct ImportDeclarationNode : DeclarationNode {
  QualifiedNameNode* name;
  std::optional<std::string> alias;
  SymbolId resolved_symbol_id;

  explicit ImportDeclarationNode(QualifiedNameNode* n) : DeclarationNode(NodeKind::ImportDeclaration), name(n) {}

  
};
} // namespace ayla::ast::node
