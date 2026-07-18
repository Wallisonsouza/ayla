#pragma once

#include "ast/PatternNode.hpp"
#include "ast/StatementNode.hpp"
#include "syntax/parser/DeclarationSpecifiers.hpp"

namespace ayla::ast::node {

struct VariableDeclarationNode : StatementNode {
  PatternNode *pattern;
  ExpressionNode *initializer;
  DeclarationSpecifiers specifiers;

  VariableDeclarationNode(PatternNode *p, ExpressionNode *init, DeclarationSpecifiers specifiers = {}) : StatementNode(NodeKind::VariableDeclaration), pattern(p), initializer(init), specifiers(specifiers) {}

  
};

} // namespace ayla::ast::node
