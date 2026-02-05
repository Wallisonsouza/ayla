#pragma once

#include "engine/parser/node/statement_nodes.hpp"
#include "frontend/ast/StatementNode.hpp"
#include "frontend/ast/statements/BlockStatementNode.hpp"

namespace ayla::ast::node {

struct FunctionDeclarationNode : StatementNode {
  IdentifierNode *identifier;
  std::vector<PatternNode *> params;
  TypeNode *return_type;
  BlockStatementNode *body;
  Modifiers modifiers;
  SymbolId symbol_id;

  FunctionDeclarationNode(IdentifierNode *identifier, std::vector<PatternNode *> params, TypeNode *ret_type = nullptr, BlockStatementNode *b = nullptr, Modifiers mods = {})
      : StatementNode(NodeKind::FunctionDeclaration), identifier(identifier), params(std::move(params)), return_type(ret_type), body(b), modifiers(mods) {}
};
} // namespace ayla::ast::node
