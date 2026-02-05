
#include "engine/parser/parser.hpp"
#include "frontend/ast/statements/ImportStatementNode.hpp"

ayla::ast::StatementNode *Parser::parse_import_statement() {

  if (!unit.tokens.match(TokenKind::IMPORT_KEYWORD)) return nullptr;

  std::vector<ayla::ast::IdentifierNode *> path_nodes;

  // primeiro identificador é obrigatório
  auto *name_token = unit.tokens.match(TokenKind::IDENTIFIER);
  if (!name_token) {
    report_error(DiagnosticCode::ExpectedToken, "expected module name after 'import'", unit.tokens.peek_slice());
    return nullptr;
  }

  while (true) {
    auto name = unit.source.buffer.get_text(name_token->slice.span);
    path_nodes.push_back(unit.ast.create_node<ayla::ast::IdentifierNode>(name));

    if (!unit.tokens.match(TokenKind::DOT)) break;

    name_token = unit.tokens.match(TokenKind::IDENTIFIER);
    if (!name_token) {
      report_error(DiagnosticCode::ExpectedToken, "expected identifier after '.' in import path", unit.tokens.peek_slice());
      break;
    }
  }

  auto *node = unit.ast.create_node<ayla::ast::node::ImportStatementNode>(std::move(path_nodes));
  node->slice = unit.tokens.last_slice();
  return node;
}
