#pragma once
#include "ast/StatementNode.hpp"
#include "ast/expressions/IdentifierExpressionNode.hpp"
#include <optional>

namespace ayla::ast::node {

struct ImportStatementNode : StatementNode {
  QualifiedNameNode* name;
  std::optional<std::string> alias;
  SymbolId resolved_symbol_id;

  explicit ImportStatementNode(QualifiedNameNode* n) : StatementNode(NodeKind::ImportStatement), name(n) {}

  
};
} // namespace ayla::ast::node
