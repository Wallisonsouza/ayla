#pragma once

#include "celestia/ast/names/IdentifierNode.hpp"
#include "celestia/ast/statements/StatementNode.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"

namespace celestia::ast {

struct Declaration : Statement {

  bool resolved = false;
  explicit Declaration(NodeKind k) : Statement(k) {}
};

struct NamedDeclaration : Declaration {

  IdentifierNode *name;
  DeclarationSpecifiers specifiers;

  NamedDeclaration(NodeKind kind, IdentifierNode *name, DeclarationSpecifiers specifiers) : Declaration(kind), name(name), specifiers(specifiers) {}
};
} // namespace celestia::ast