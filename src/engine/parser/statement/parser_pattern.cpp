
#include "engine/parser/parser.hpp"

ayla::ast::PatternNode *Parser::parse_pattern() {
  auto *id = parse_identifier();
  if (!id) return nullptr;

  ayla::ast::TypeNode *type = nullptr;

  if (unit.tokens.match(TokenKind::COLON)) { type = parse_type(); }

  return unit.ast.create_node<ayla::ast::IdentifierPatternNode>(id, type);
}
