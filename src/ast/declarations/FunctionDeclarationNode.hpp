#pragma once

#include "ast/declarations/DeclarationNode.hpp"
#include "ast/patterns/PatternNode.hpp"
#include "ast/names/QualifiedNameNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "semantic/symbols/SymbolId.hpp"
#include "syntax/parser/DeclarationSpecifiers.hpp"

namespace ayla::ast::node {

struct FunctionDeclarationNode : DeclarationNode {
  NameNode *name;
  std::vector<PatternNode *> parameters;
  TypeNode *return_type;
  BlockStatementNode *body;
  DeclarationSpecifiers specifiers;
  SymbolId symbol_id; 

  FunctionDeclarationNode(NameNode *n, std::vector<PatternNode *> params = {}, TypeNode *ret_type = nullptr, BlockStatementNode *b = nullptr, DeclarationSpecifiers s = {})
      : DeclarationNode(NodeKind::FunctionDeclaration), name(n), parameters(std::move(params)), return_type(ret_type), body(b), specifiers(s) {}

  
};
} // namespace ayla::ast::node
