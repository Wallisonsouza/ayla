#pragma once
#include "core/memory/symbol.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include <optional>
#include <string>
#include <vector>

namespace parser::node::statement {

struct ModuleDeclarationNode : core::ast::ASTStatementNode {
  std::vector<core::ast::IdentifierNode *> path;
  std::vector<ASTNode *> body;
  SymbolId resolved_symbol_id;

  ModuleDeclarationNode(std::vector<core::ast::IdentifierNode *> p, std::vector<ASTNode *> b)
      : core::ast::ASTStatementNode(core::ast::NodeKind::ModuleDeclaration), path(std::move(p)), body(std::move(b)) {}
};

struct ImportNode : core::ast::ASTStatementNode {
  std::vector<core::ast::IdentifierNode *> path;
  std::optional<std::string> alias;
  SymbolId resolved_symbol_id;

  explicit ImportNode(std::vector<core::ast::IdentifierNode *> p) : ASTStatementNode(core::ast::NodeKind::Import), path(std::move(p)) {}
};

struct AssignmentNode : core::ast::ASTExpressionNode {
  core::ast::ASTExpressionNode *target;
  core::ast::ASTExpressionNode *value;

  AssignmentNode(core::ast::ASTExpressionNode *t, core::ast::ASTExpressionNode *v) : ASTExpressionNode(core::ast::NodeKind::Assignment), target(t), value(v) {}
};

struct InterfaceNode : core::ast::ASTNode {
  core::ast::IdentifierNode *name;
  std::vector<core::ast::ASTNode *> members;

  InterfaceNode(core::ast::IdentifierNode *n, std::vector<core::ast::ASTNode *> m)
      : core::ast::ASTNode(core::ast::NodeKindBase::Unknown, core::ast::NodeKind::Interface), name(n), members(std::move(m)) {}
};

} // namespace parser::node::statement
