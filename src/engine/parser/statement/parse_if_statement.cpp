#include "core/node/Type.hpp"
#include "core/node/flags.hpp"

#include "engine/parser/parser.hpp"
#include "frontend/ast/statements/IfStatementNode.hpp"

ayla::ast::StatementNode *Parser::parse_if_statement() {
  if (!unit.tokens.match(TokenKind::IF_KEYWORD)) return nullptr;

  auto *condition = parse_expression();
  if (!condition || condition->flags.has(NodeFlags::HasError)) {

    report_error(DiagnosticCode::ConditionMissing, "expected condition after 'if'");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  if (condition->kind == ayla::ast::NodeKind::Assignment) {

    report_error(DiagnosticCode::ConditionAssignment, "assignment is not allowed in if condition");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  auto *then_block = parse_block_statement();

  if (then_block->flags.has(NodeFlags::HasError)) {

    report_error(DiagnosticCode::BlockError, "error in then block");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  ayla::ast::StatementNode *else_block = nullptr;
  if (unit.tokens.match(TokenKind::ELSE_KEYWORD)) {
    if (unit.tokens.peek(TokenKind::IF_KEYWORD)) {
      else_block = parse_if_statement();
    } else {
      else_block = parse_block_statement();
    }

    if (else_block && else_block->flags.has(NodeFlags::HasError)) {

      report_error(DiagnosticCode::BlockError, "error in else block");

      recover_until(RecoverBoundary::If);

      return nullptr;
    }
  }

  return unit.ast.create_node<ayla::ast::node::IfStatementNode>(condition, then_block, else_block);
}
