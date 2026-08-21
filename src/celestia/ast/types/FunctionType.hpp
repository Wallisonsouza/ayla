#pragma once

#include "celestia/ast/types/TypeNode.hpp"
#include <vector>

namespace celestia::ast {

class FunctionType : public TypeNode {

  std::vector<TypeNode *> parameters_;
  TypeNode *return_type_;

public:
  FunctionType(std::vector<TypeNode *> parameters, TypeNode *return_type) : TypeNode(NodeKind::FunctionType), parameters_(std::move(parameters)), return_type_(return_type) {}
};

} // namespace celestia::ast