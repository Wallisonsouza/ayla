#pragma once

#include "Declaration.hpp"

#include "celestia/ast/declarations/FunctionDeclaration.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"
#include "celestia/ast/types/TypeNode.hpp"

#include <utility>
#include <vector>

namespace celestia::ast {

struct ImplDeclaration : Declaration {

  std::vector<IdentifierNode *> generic_parameters;

  TypeNode *target;

  TypeNode *capability;

  std::vector<FunctionDeclaration *> members;

  ImplDeclaration(std::vector<IdentifierNode *> generic_parameters, TypeNode *target, TypeNode *capability, std::vector<FunctionDeclaration *> members)
      : Declaration(NodeKind::ImplementationDeclaration), generic_parameters(std::move(generic_parameters)), target(target), capability(capability), members(std::move(members)) {}
};

} // namespace celestia::ast