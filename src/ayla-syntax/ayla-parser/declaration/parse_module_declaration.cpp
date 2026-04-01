#include "ayla-syntax/ayla-parser/parser.hpp"

parser::node::statement::ModuleDeclarationNode *Parser::parse_module_declaration() {

  if (!unit.tokens.match(ayla::structural::token::TokenKind::MODULE_KEYWORD)) return nullptr;

  std::vector<core::ast::IdentifierNode *> path;

  auto *id = parse_identifier();
  if (!id) {
    report_error(DiagnosticCode::ExpectedIdentifier, "module name");
    return nullptr;
  }
  path.push_back(id);

  while (unit.tokens.match(ayla::structural::token::TokenKind::DOT)) {
    auto *next_id = parse_identifier();
    if (!next_id) {
      report_error(DiagnosticCode::ExpectedIdentifier, "submodule name after '.'");
      break;
    }
    path.push_back(next_id);
  }

  if (!unit.tokens.match(ayla::structural::token::TokenKind::OPEN_BRACE)) {
    report_error(DiagnosticCode::ExpectedToken, "'{' to start module body");
    return nullptr;
  }

  std::vector<core::ast::ASTNode *> body;

  while (!unit.tokens.match(ayla::structural::token::TokenKind::CLOSE_BRACE) && !unit.tokens.is_end()) {
    auto *node = parse_statement();
    if (node) body.push_back(node);
  }

  return unit.ast.create_node<parser::node::statement::ModuleDeclarationNode>(std::move(path), std::move(body));
}
