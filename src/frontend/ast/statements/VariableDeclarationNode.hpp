#pragma once

#include "core/node/Modifier.hpp"
#include "core/node/Type.hpp"
#include "frontend/ast/StatementNode.hpp"

namespace ayla::ast::node {

struct VariableDeclarationNode : StatementNode {
  PatternNode *pattern;
  ExpressionNode *initializer;
  Modifiers modifiers;

  VariableDeclarationNode(PatternNode *p, ExpressionNode *init, Modifiers m = {}) : StatementNode(NodeKind::VariableDeclaration), pattern(p), initializer(init), modifiers(m) {}
};

} // namespace ayla::ast::node
