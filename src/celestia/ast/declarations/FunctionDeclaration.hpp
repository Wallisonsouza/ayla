#pragma once

#include "Declaration.hpp"
#include "celestia/ast/names/IdentifierNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/types/TypeNode.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"

namespace celestia::ast {

struct FunctionDeclaration : NamedDeclaration {
  std::vector<PatternNode *> parameters;
  TypeNode *return_type;
  BlockStatement *body;
  SymbolId symbol_id;

  FunctionDeclaration(IdentifierNode *n = nullptr, std::vector<PatternNode *> params = {}, TypeNode *ret_type = nullptr, BlockStatement *b = nullptr, DeclarationSpecifiers s = {})
      : NamedDeclaration(NodeKind::FunctionDeclaration, n, s), parameters(std::move(params)), return_type(ret_type), body(b) {}
};
} // namespace celestia::ast
