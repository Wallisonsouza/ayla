#pragma once

#include "celestia/ast/declarations/DeclarationNode.hpp"
#include "celestia/ast/ExpressionNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"

namespace celestia::ast::node {

struct VariableDeclarationNode : DeclarationNode {
  PatternNode *pattern;
  ExpressionNode *initializer;
  DeclarationSpecifiers specifiers;

  VariableDeclarationNode(PatternNode *p, ExpressionNode *init, DeclarationSpecifiers specifiers = {}) : DeclarationNode(NodeKind::VariableDeclaration), pattern(p), initializer(init), specifiers(specifiers) {}
};

} // namespace celestia::ast::node
