#include "ayla-syntax/ayla-parser/parser.hpp"

core::ast::PatternNode *Parser::parse_pattern(core::ast::Modifiers mods) {
  auto start = unit.tokens.peek_slice();

  auto *id_node = parse_identifier();

  if (!id_node) {

    auto *tok = unit.tokens.peek();
    std::string found = tok ? tok->descriptor->name : "EOF";
    report_error(DiagnosticCode::ExpectedIdentifier, "Expected parameter name");

    return unit.ast.create_node<core::ast::PatternErrorNode>(start, mods);
  }

  core::ast::TypeNode *type_node = nullptr;
  if (unit.tokens.match(TokenKind::COLON)) {
    type_node = parse_type();
    if (!type_node) {
      report_error(DiagnosticCode::ExpectedType, "type");
      return unit.ast.create_node<core::ast::PatternErrorNode>(start, mods);
    }
  }

  core::ast::ASTExpressionNode *value_node = nullptr;
  if (unit.tokens.match(TokenKind::ASSIGN)) {
    value_node = parse_expression();
    if (!value_node) {
      report_error(DiagnosticCode::ExpectedExpression, "expression after '='");
      return unit.ast.create_node<core::ast::PatternErrorNode>(start, mods);
    }
  }

  return unit.ast.create_node<core::ast::PatternNode>(id_node, type_node, value_node, mods);
}
