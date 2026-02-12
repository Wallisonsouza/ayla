#pragma once

#include "ast/PatternNode.hpp"
#include "ast/StatementNode.hpp"
#include "ast/expressions/IdentifierExpressionNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "core/node/Modifier.hpp"
#include "semantic/symbols/SymbolId.hpp"

namespace ayla::ast::node {

struct FunctionDeclarationNode : StatementNode {
  IdentifierExpressionNode *identifier;
  std::vector<PatternNode *> parameters;
  TypeNode *return_type;
  BlockStatementNode *body;
  Modifiers modifiers;
  SymbolId symbol_id;

  FunctionDeclarationNode(IdentifierExpressionNode *identifier, std::vector<PatternNode *> params, TypeNode *ret_type = nullptr, BlockStatementNode *b = nullptr, Modifiers mods = {})
      : StatementNode(NodeKind::FunctionDeclaration), identifier(identifier), parameters(std::move(params)), return_type(ret_type), body(b), modifiers(mods) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};
} // namespace ayla::ast::node
