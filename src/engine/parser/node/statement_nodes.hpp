#pragma once

#include "core/module/scope.hpp"
#include "core/node/Modifier.hpp"
#include "core/node/Type.hpp"
#include "core/node/flags.hpp"

namespace parser::node {

struct BlockStatementNode : ayla::ast::StatementNode {
  std::vector<ayla::ast::StatementNode *> statements;

  explicit BlockStatementNode(std::vector<ayla::ast::StatementNode *> stmts = {}) : StatementNode(ayla::ast::NodeKind::BlockStatement), statements(std::move(stmts)) {}
};

struct ASTWhileStatementNode : ayla::ast::StatementNode {
  ayla::ast::ExpressionNode *condition;
  BlockStatementNode *body;

  ASTWhileStatementNode(ayla::ast::ExpressionNode *cond, BlockStatementNode *block) : ayla::ast::StatementNode(ayla::ast::NodeKind::WhileStatement), condition(cond), body(block) {}
};

struct IfStatementNode : ayla::ast::StatementNode {
  ayla::ast::ExpressionNode *condition;
  BlockStatementNode *then_block;
  ayla::ast::StatementNode *else_block;

  IfStatementNode(ayla::ast::ExpressionNode *cond, BlockStatementNode *then_b, ayla::ast::StatementNode *else_b = nullptr)
      : ayla::ast::StatementNode(ayla::ast::NodeKind::IfStatement), condition(cond), then_block(then_b), else_block(else_b) {}
};

struct MemberAccessNode : ayla::ast::ExpressionNode {
  ayla::ast::ExpressionNode *base;
  ayla::ast::IdentifierNode *field;

  MemberAccessNode(ayla::ast::ExpressionNode *b, ayla::ast::IdentifierNode *f) : ayla::ast::ExpressionNode(ayla::ast::NodeKind::MemberAccess), base(b), field(f) {}
};

} // namespace parser::node