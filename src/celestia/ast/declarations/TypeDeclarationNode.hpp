#pragma once

#include "celestia/ast/declarations/DeclarationNode.hpp"
#include <string>
#include <vector>

namespace celestia::ast::node {

struct TypeDeclarationNode : DeclarationNode {
  std::string name;
  std::vector<std::string> type_params;

  explicit TypeDeclarationNode(std::string n, std::vector<std::string> params = {}) : DeclarationNode(NodeKind::TypeDeclaration), name(std::move(n)), type_params(std::move(params)) {}

  // 
};

} // namespace celestia::ast::node
