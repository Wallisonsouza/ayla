#pragma once
#include "core/module/module.hpp"
#include "core/node/Type.hpp"
#include <optional>

namespace ayla::ast::node {

struct ImportStatementNode : StatementNode {
  std::vector<IdentifierNode *> path;
  std::optional<std::string> alias;
  ModuleId resolved_module_id;
  SymbolId resolved_symbol_id;

  explicit ImportStatementNode(std::vector<IdentifierNode *> p) : StatementNode(NodeKind::Import), path(std::move(p)) {}
};
} // namespace ayla::ast::node
