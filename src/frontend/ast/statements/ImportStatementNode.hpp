#pragma once
#include "core/module/module.hpp"
#include "frontend/ast/expressions/IdentifierExpressionNode.hpp"
#include <optional>

namespace ayla::ast::node {

struct ImportStatementNode : StatementNode {
  std::vector<IdentifierExpressionNode *> path;
  std::optional<std::string> alias;
  ModuleId resolved_module_id;
  SymbolId resolved_symbol_id;

  explicit ImportStatementNode(std::vector<IdentifierExpressionNode *> p) : StatementNode(NodeKind::Import), path(std::move(p)) {}
};
} // namespace ayla::ast::node
