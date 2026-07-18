#pragma once
#include "ast/expressions/IdentifierExpressionNode.hpp"
#include <optional>

namespace ayla::ast::node {

struct ImportStatementNode : StatementNode {
  std::vector<IdentifierExpressionNode *> path;
  std::optional<std::string> alias;
  SymbolId resolved_symbol_id;

  explicit ImportStatementNode(std::vector<IdentifierExpressionNode *> p) : StatementNode(NodeKind::ImportStatement), path(std::move(p)) {}

  
};
} // namespace ayla::ast::node
