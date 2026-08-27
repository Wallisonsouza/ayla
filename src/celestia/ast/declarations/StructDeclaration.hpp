#pragma once

#include "Declaration.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"
#include "celestia/ast/types/TypeNode.hpp"

#include <utility>
#include <vector>

namespace celestia::ast {

struct FieldDeclaration : Node {

  IdentifierNode *name;
  TypeNode *type;

  FieldDeclaration(IdentifierNode *name, TypeNode *type) : Node(NodeKind::FieldDeclaration), name(name), type(type) {}
};

struct StructDeclaration : NamedDeclaration {

  std::vector<TypeNode *> compositions;
  std::vector<FieldDeclaration *> fields;

  StructDeclaration(IdentifierNode *name,
                    std::vector<IdentifierNode *> generic_parameters,
                    std::vector<TypeNode *> compositions,
                    std::vector<FieldDeclaration *> fields,
                    DeclarationSpecifiers specifiers)
      : NamedDeclaration(NodeKind::StructDeclaration, name, specifiers, std::move(generic_parameters)), compositions(std::move(compositions)), fields(std::move(fields)) {}
};

} // namespace celestia::ast