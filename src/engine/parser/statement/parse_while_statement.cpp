#include "core/node/Type.hpp"
#include "core/node/flags.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

parser::node::ASTWhileStatementNode *Parser::parse_while_statemente() {

  if (!unit.tokens.match(TokenKind::WHILE_KEYWORD)) return nullptr;

  auto *condition = parse_expression();

  if (!condition || condition->flags.has(NodeFlags::HasError)) {

    report_error(DiagnosticCode::ConditionMissing, "expected condition after 'while'");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  if (condition->kind == core::ast::NodeKind::Assignment) {

    report_error(DiagnosticCode::ConditionAssignment, "assignment is not allowed in if condition");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  auto *block = parse_block_statement();

  if (block->flags.has(NodeFlags::HasError)) {

    report_error(DiagnosticCode::BlockError, "error in while block");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  return unit.ast.create_node<parser::node::ASTWhileStatementNode>(condition, block);
}
