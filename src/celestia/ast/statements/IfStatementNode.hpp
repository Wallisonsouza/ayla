#pragma once

#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/ast/statements/StatementNode.hpp"

namespace celestia::ast {

struct IfStatement : Statement {
  Expression *condition;
  Statement *then_block;
  Statement *else_block;

  IfStatement(Expression *cond, Statement *then_b, Statement *else_b = nullptr) : Statement(NodeKind::IfStatement), condition(cond), then_block(then_b), else_block(else_b) {}
};
} // namespace celestia::ast
