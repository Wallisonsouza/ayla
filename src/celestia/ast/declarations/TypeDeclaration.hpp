#pragma once

#include "Declaration.hpp"
#include <string>
#include <vector>

namespace celestia::ast {

struct TypeDeclaration : Declaration {
  std::string name;
  std::vector<std::string> type_params;

  explicit TypeDeclaration(std::string n, std::vector<std::string> params = {}) : Declaration(NodeKind::TypeDeclaration), name(std::move(n)), type_params(std::move(params)) {}

  //
};

} // namespace celestia::ast
