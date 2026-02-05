#pragma once
#include "core/module/module.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "frontend/ast/AstNode.hpp"
#include <optional>
#include <string>
#include <vector>

namespace parser::node::statement {

struct ModuleDeclarationNode : core::ast::ASTStatementNode {
  std::vector<core::ast::IdentifierNode *> path;
  std::vector<AstNode *> body;
  ModuleId resolved_module_id;
  SymbolId resolved_symbol_id;

  ModuleDeclarationNode(std::vector<core::ast::IdentifierNode *> p, std::vector<AstNode *> b)
      : core::ast::ASTStatementNode(core::ast::NodeKind::ModuleDeclaration), path(std::move(p)), body(std::move(b)) {}
};

struct ImportNode : core::ast::ASTStatementNode {
  std::vector<core::ast::IdentifierNode *> path;
  std::optional<std::string> alias;
  ModuleId resolved_module_id;
  SymbolId resolved_symbol_id;

  explicit ImportNode(std::vector<core::ast::IdentifierNode *> p) : ASTStatementNode(core::ast::NodeKind::Import), path(std::move(p)) {}
};

struct AssignmentNode : core::ast::ASTExpressionNode {
  core::ast::ASTExpressionNode *target;
  core::ast::ASTExpressionNode *value;

  AssignmentNode(core::ast::ASTExpressionNode *t, core::ast::ASTExpressionNode *v) : ASTExpressionNode(core::ast::NodeKind::Assignment), target(t), value(v) {}
};

struct InterfaceNode : ayla::ast::AstNode {
  core::ast::IdentifierNode *name;
  std::vector<ayla::ast::AstNode *> members;

  InterfaceNode(core::ast::IdentifierNode *n, std::vector<ayla::ast::AstNode *> m) : ayla::ast::AstNode(core::ast::NodeKind::Interface), name(n), members(std::move(m)) {}
};

} // namespace parser::node::statement
