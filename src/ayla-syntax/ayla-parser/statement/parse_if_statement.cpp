#include "ayla-structural/ayla-ast/statement_nodes.hpp"
#include "ayla-syntax/ayla-parser/parser.hpp"
#include "core/node/Type.hpp"
#include "core/node/flags.hpp"

core::ast::ASTStatementNode *Parser::parse_if_statement() {
  if (!unit.tokens.match(ayla::structural::token::TokenKind::IF_KEYWORD)) return nullptr;

  auto *condition = parse_expression();
  if (!condition || condition->flags.has(NodeFlags::HasError)) {

    report_error(DiagnosticCode::ConditionMissing, "expected condition after 'if'");

    recover_until(RecoverBoundary::If);

    return unit.ast.create_node<parser::node::IfStatementNodeError>();
  }

  if (condition->kind == core::ast::NodeKind::Assignment) {

    report_error(DiagnosticCode::ConditionAssignment, "assignment is not allowed in if condition");

    recover_until(RecoverBoundary::If);

    return unit.ast.create_node<parser::node::IfStatementNodeError>();
  }

  auto *then_block = parse_block_statement();

  if (then_block->flags.has(NodeFlags::HasError)) {

    report_error(DiagnosticCode::BlockError, "error in then block");

    recover_until(RecoverBoundary::If);

    return unit.ast.create_node<parser::node::IfStatementNodeError>();
  }

  core::ast::ASTStatementNode *else_block = nullptr;
  if (unit.tokens.match(ayla::structural::token::TokenKind::ELSE_KEYWORD)) {
    if (unit.tokens.peek(ayla::structural::token::TokenKind::IF_KEYWORD)) {
      else_block = parse_if_statement();
    } else {
      else_block = parse_block_statement();
    }

    if (else_block && else_block->flags.has(NodeFlags::HasError)) {

      report_error(DiagnosticCode::BlockError, "error in else block");

      recover_until(RecoverBoundary::If);

      return unit.ast.create_node<parser::node::IfStatementNodeError>();
    }
  }

  return unit.ast.create_node<parser::node::IfStatementNode>(condition, then_block, else_block);
}
