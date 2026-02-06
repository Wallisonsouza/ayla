
#pragma once

#include "frontend/ast/ExpressionNode.hpp"
#include <string>

namespace ayla::ast::node {

struct IdentifierExpressionNode : ExpressionNode {
  std::string name;
  explicit IdentifierExpressionNode(std::string n) : ExpressionNode(NodeKind::Identifier), name(std::move(n)) {}

  void accept(AstVisitor &v) override { v.visit(this); }
  
};
} // namespace ayla::ast::node