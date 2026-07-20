#pragma once
#include "ast/declarations/DeclarationNode.hpp"
#include "ast/names/QualifiedNameNode.hpp"
#include "semantic/symbols/SymbolId.hpp"

namespace ayla::ast::node {

struct ModuleDeclarationNode : DeclarationNode {

  QualifiedNameNode* name;
  std::vector<AstNode *> body;
  SymbolId resolved_symbol_id;

  ModuleDeclarationNode(QualifiedNameNode* n, std::vector<AstNode *> b) : DeclarationNode(NodeKind::ModuleDeclaration), name(n), body(std::move(b)) {}

  
};

} // namespace ayla::ast::node
