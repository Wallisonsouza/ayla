#pragma once

#include "celestia/ast/declarations/DeclarationNode.hpp"
#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"

namespace celestia::ast {

struct VariableDeclarationNode : Declaration {
  PatternNode *pattern;
  Expression *initializer;
  DeclarationSpecifiers specifiers;

  VariableDeclarationNode(PatternNode *p, Expression *init, DeclarationSpecifiers specifiers = {}) : Declaration(NodeKind::VariableDeclaration), pattern(p), initializer(init), specifiers(specifiers) {}
};

} // namespace celestia::ast
