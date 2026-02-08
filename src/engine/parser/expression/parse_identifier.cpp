#include "engine/parser/parser.hpp"

ayla::ast::node::IdentifierExpressionNode *Parser::parse_identifier() {

  Token *token = unit.tokens.match(TokenKind::IDENTIFIER);
  if (!token) return nullptr;

  auto *node = unit.ast.create_node<ayla::ast::node::IdentifierExpressionNode>(unit.source.buffer.get_text(token->slice.span));
  node->slice = token->slice;

  return node;
}
