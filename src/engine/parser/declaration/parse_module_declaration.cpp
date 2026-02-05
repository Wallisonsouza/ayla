#include "core/token/TokenKind.hpp"
#include "engine/parser/parser.hpp"

parser::node::statement::ModuleDeclarationNode *Parser::parse_module_declaration() {

  if (!unit.tokens.match(TokenKind::MODULE_KEYWORD)) return nullptr;

  std::vector<ayla::ast::IdentifierNode *> path;

  auto *id = parse_identifier();
  if (!id) {
    report_error(DiagnosticCode::ExpectedIdentifier, "module name");
    return nullptr;
  }
  path.push_back(id);

  while (unit.tokens.match(TokenKind::DOT)) {
    auto *next_id = parse_identifier();
    if (!next_id) {
      report_error(DiagnosticCode::ExpectedIdentifier, "submodule name after '.'");
      break;
    }
    path.push_back(next_id);
  }

  if (!unit.tokens.match(TokenKind::OPEN_BRACE)) {
    report_error(DiagnosticCode::ExpectedToken, "'{' to start module body");
    return nullptr;
  }

  std::vector<ayla::ast::AstNode *> body;

  while (!unit.tokens.match(TokenKind::CLOSE_BRACE) && !unit.tokens.is_end()) {
    auto *node = parse_statement();
    if (node) body.push_back(node);
  }

  return unit.ast.create_node<parser::node::statement::ModuleDeclarationNode>(std::move(path), std::move(body));
}
