#pragma once

#include "ast/StatementNode.hpp"
#include <string>
#include <vector>

namespace ayla::ast::node {

struct TypeDeclarationNode : StatementNode {
  std::string name;
  std::vector<std::string> type_params;

  explicit TypeDeclarationNode(std::string n, std::vector<std::string> params = {}) : StatementNode(NodeKind::TypeDeclaration), name(std::move(n)), type_params(std::move(params)) {}

  // void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node
