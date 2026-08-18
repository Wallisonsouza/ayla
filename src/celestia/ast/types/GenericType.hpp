#pragma once

#include "celestia/ast/types/TypeNode.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"

namespace celestia::ast {

struct GenericType : TypeNode {

  IdentifierNode *name;
  std::vector<TypeNode *> arguments;

  GenericType(IdentifierNode *name, std::vector<TypeNode *> arguments) : TypeNode(NodeKind::GenericType), name(name), arguments(std::move(arguments)) {}
};
} // namespace celestia::ast