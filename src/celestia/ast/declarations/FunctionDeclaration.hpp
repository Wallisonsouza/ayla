#pragma once

#include "Declaration.hpp"
#include "celestia/ast/TypeNode.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"

namespace celestia::ast {

struct FunctionDeclaration : Declaration {
  IdentifierNode *name;
  std::vector<PatternNode *> parameters;
  TypeNode *return_type;
  BlockStatement *body;
  DeclarationSpecifiers specifiers;
  SymbolId symbol_id;

  FunctionDeclaration(IdentifierNode *n = nullptr, std::vector<PatternNode *> params = {}, TypeNode *ret_type = nullptr, BlockStatement *b = nullptr, DeclarationSpecifiers s = {})
      : Declaration(NodeKind::FunctionDeclaration), name(n), parameters(std::move(params)), return_type(ret_type), body(b), specifiers(s) {}
};
} // namespace celestia::ast
