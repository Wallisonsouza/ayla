#pragma once

#include "Declaration.hpp"
#include "celestia/ast/declarations/FunctionDeclaration.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"

namespace celestia::ast {

struct CapabilityDeclaration : NamedDeclaration {
  std::vector<FunctionDeclaration *> members;

  CapabilityDeclaration(IdentifierNode *name, std::vector<FunctionDeclaration *> members, DeclarationSpecifiers specifiers)
      : NamedDeclaration(NodeKind::CapabilityDeclaration, name, specifiers), members(std::move(members)) {}
};
} // namespace celestia::ast
