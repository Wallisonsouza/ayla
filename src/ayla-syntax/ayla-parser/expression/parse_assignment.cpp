#include "ayla-structural/ayla-ast/statements/ImportStatement.hpp"
#include "ayla-syntax/ayla-parser/parser.hpp"
#include "core/node/Type.hpp"

core::ast::ASTExpressionNode *Parser::parse_assignment(core::ast::ASTExpressionNode *target) {

  if (!unit.tokens.match(TokenKind::ASSIGN)) { return nullptr; }

  auto start = unit.tokens.peek_slice();

  auto *value = parse_expression();

  if (!value) {
    // unit.diagnostics.emit(
    //     {DiagnosticCode::InvalidAssignment, stream.last_slice(), {}}, unit);
    // return nullptr;
  }

  auto node = unit.ast.create_node<parser::node::statement::AssignmentNode>(target, value);
  node->slice = start;
  return node;
}
