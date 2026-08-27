#pragma once

#include "celestia/ast/names/IdentifierNode.hpp"
#include "celestia/ast/statements/StatementNode.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"

#include <vector>

namespace celestia::ast {

struct Declaration : Statement {
  explicit Declaration(NodeKind k) : Statement(k) {}
};

struct NamedDeclaration : Declaration {
  IdentifierNode *name;
  DeclarationSpecifiers specifiers;
  std::vector<IdentifierNode *> generic_parameters;

  NamedDeclaration(NodeKind kind, IdentifierNode *name, DeclarationSpecifiers specifiers, std::vector<IdentifierNode *> generic_parameters = {})
      : Declaration(kind), name(name), specifiers(specifiers), generic_parameters(std::move(generic_parameters)) {}
};

} // namespace celestia::ast