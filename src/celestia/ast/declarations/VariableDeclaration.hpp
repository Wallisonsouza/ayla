#pragma once

#include "Declaration.hpp"
#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"

namespace celestia::ast {

struct VariableDeclaration : Declaration {
  PatternNode *pattern;
  Expression *initializer;
  DeclarationSpecifiers specifiers;

  VariableDeclaration(PatternNode *p, Expression *init, DeclarationSpecifiers specifiers = {}) : Declaration(NodeKind::VariableDeclaration), pattern(p), initializer(init), specifiers(specifiers) {}
};

} // namespace celestia::ast
