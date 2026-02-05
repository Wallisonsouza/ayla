#pragma once
#include "core/module/module.hpp"
#include "core/node/Type.hpp"
#include "frontend/ast/AstNode.hpp"
#include <optional>
#include <string>
#include <vector>

namespace parser::node::statement {

struct ModuleDeclarationNode : ayla::ast::ASTStatementNode {
  std::vector<ayla::ast::IdentifierNode *> path;
  std::vector<AstNode *> body;
  ModuleId resolved_module_id;
  SymbolId resolved_symbol_id;

  ModuleDeclarationNode(std::vector<ayla::ast::IdentifierNode *> p, std::vector<AstNode *> b)
      : ayla::ast::ASTStatementNode(ayla::ast::NodeKind::ModuleDeclaration), path(std::move(p)), body(std::move(b)) {}
};

struct ImportNode : ayla::ast::ASTStatementNode {
  std::vector<ayla::ast::IdentifierNode *> path;
  std::optional<std::string> alias;
  ModuleId resolved_module_id;
  SymbolId resolved_symbol_id;

  explicit ImportNode(std::vector<ayla::ast::IdentifierNode *> p) : ASTStatementNode(ayla::ast::NodeKind::Import), path(std::move(p)) {}
};

struct AssignmentNode : ayla::ast::ExpressionNode {
  ayla::ast::ExpressionNode *target;
  ayla::ast::ExpressionNode *value;

  AssignmentNode(ayla::ast::ExpressionNode *t, ayla::ast::ExpressionNode *v) : ayla::ast::ExpressionNode(ayla::ast::NodeKind::Assignment), target(t), value(v) {}
};

} // namespace parser::node::statement
