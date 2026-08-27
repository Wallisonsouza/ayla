#pragma once

#include "celestia/ast/types/TypeNode.hpp"
#include <vector>

namespace celestia::ast {

struct FunctionType : public TypeNode {

  std::vector<TypeNode *> parameters;
  TypeNode *return_type;

public:
  FunctionType(std::vector<TypeNode *> parameters, TypeNode *return_type) : TypeNode(NodeKind::FunctionType), parameters(std::move(parameters)), return_type(return_type) {}
};

} // namespace celestia::ast