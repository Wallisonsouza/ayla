#pragma once

#include "ast/PatternNode.hpp"
#include "ast/StatementNode.hpp"
#include "ast/expressions/IdentifierExpressionNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "semantic/symbols/SymbolId.hpp"
#include "syntax/parser/DeclarationSpecifiers.hpp"

namespace ayla::ast::node {

struct FunctionDeclarationNode : StatementNode {
  IdentifierExpressionNode *identifier;
  std::vector<PatternNode *> parameters;
  TypeNode *return_type;
  BlockStatementNode *body;
  DeclarationSpecifiers specifiers;
  SymbolId symbol_id; 

  FunctionDeclarationNode(IdentifierExpressionNode *identifier, std::vector<PatternNode *> params, TypeNode *ret_type = nullptr, BlockStatementNode *b = nullptr, DeclarationSpecifiers s = {})
      : StatementNode(NodeKind::FunctionDeclaration), identifier(identifier), parameters(std::move(params)), return_type(ret_type), body(b), specifiers(s) {}

  
};
} // namespace ayla::ast::node
