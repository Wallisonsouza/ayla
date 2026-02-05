#pragma once

#include "core/module/scope.hpp"
#include "core/node/Modifier.hpp"
#include "core/node/Type.hpp"
#include "core/node/flags.hpp"
#include "frontend/ast/statements/BlockStatementNode.hpp"

namespace parser::node {

struct ASTWhileStatementNode : ayla::ast::StatementNode {
  ayla::ast::ExpressionNode *condition;
  ayla::ast::node::BlockStatementNode *body;

  ASTWhileStatementNode(ayla::ast::ExpressionNode *cond, ayla::ast::node::BlockStatementNode *block) : ayla::ast::StatementNode(ayla::ast::NodeKind::WhileStatement), condition(cond), body(block) {}
};

struct MemberAccessNode : ayla::ast::ExpressionNode {
  ayla::ast::ExpressionNode *base;
  ayla::ast::IdentifierNode *field;

  MemberAccessNode(ayla::ast::ExpressionNode *b, ayla::ast::IdentifierNode *f) : ayla::ast::ExpressionNode(ayla::ast::NodeKind::MemberAccess), base(b), field(f) {}
};

} // namespace parser::node