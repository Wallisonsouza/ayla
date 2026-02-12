#pragma once

#include "ast/PatternNode.hpp"
#include "ast/StatementNode.hpp"
#include "core/node/Modifier.hpp"

namespace ayla::ast::node {

struct VariableDeclarationNode : StatementNode {
  PatternNode *pattern;
  ExpressionNode *initializer;
  Modifiers modifiers;

  VariableDeclarationNode(PatternNode *p, ExpressionNode *init, Modifiers m = {}) : StatementNode(NodeKind::VariableDeclaration), pattern(p), initializer(init), modifiers(m) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};

} // namespace ayla::ast::node
