#pragma once

#include "ast/declarations/DeclarationNode.hpp"
#include "ast/ExpressionNode.hpp"
#include "ast/patterns/PatternNode.hpp"
#include "syntax/parser/DeclarationSpecifiers.hpp"

namespace ayla::ast::node {

struct VariableDeclarationNode : DeclarationNode {
  PatternNode *pattern;
  ExpressionNode *initializer;
  DeclarationSpecifiers specifiers;

  VariableDeclarationNode(PatternNode *p, ExpressionNode *init, DeclarationSpecifiers specifiers = {}) : DeclarationNode(NodeKind::VariableDeclaration), pattern(p), initializer(init), specifiers(specifiers) {}

  
};

} // namespace ayla::ast::node
