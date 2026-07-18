
#pragma once

#include "ast/ExpressionNode.hpp"
#include <string>

namespace ayla::ast::node {

struct IdentifierExpressionNode : ExpressionNode {
  std::string name;
  explicit IdentifierExpressionNode(std::string n) : ExpressionNode(NodeKind::Identifier), name(std::move(n)) {}

  
};
} // namespace ayla::ast::node