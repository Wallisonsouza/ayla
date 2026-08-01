#pragma once

#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/ast/statements/StatementNode.hpp"

namespace celestia::ast {

struct WhileStatement : Statement {
  Expression *condition;
  Statement *body;

  WhileStatement(Expression *cond, Statement *block) : Statement(NodeKind::WhileStatement), condition(cond), body(block) {}
};

} // namespace celestia::ast
