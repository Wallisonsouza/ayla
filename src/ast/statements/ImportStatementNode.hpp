#pragma once
#include "ast/expressions/IdentifierExpressionNode.hpp"
#include "core/module/module.hpp"
#include <optional>

namespace ayla::ast::node {

struct ImportStatementNode : StatementNode {
  std::vector<IdentifierExpressionNode *> path;
  std::optional<std::string> alias;
  ModuleId resolved_module_id;
  SymbolId resolved_symbol_id;

  explicit ImportStatementNode(std::vector<IdentifierExpressionNode *> p) : StatementNode(NodeKind::ImportStatement), path(std::move(p)) {}

  void accept(AstVisitor &v) override { v.visit(this); }
};
} // namespace ayla::ast::node
