#pragma once

#include "Declaration.hpp"

namespace celestia::ast {

struct TypeDeclaration : NamedDeclaration {

  TypeDeclaration(IdentifierNode *name, std::vector<IdentifierNode *> generic_parameters, DeclarationSpecifiers specifiers)
      : NamedDeclaration(NodeKind::TypeDeclaration, name, specifiers, std::move(generic_parameters)) {}
};

} // namespace celestia::ast