#include "core/token/TokenKind.hpp"
#include "engine/parser/parser.hpp"

ayla::ast::ExpressionNode *Parser::parse_primary_expression() {

  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  switch (tok->descriptor->kind) {

  case TokenKind::NUMBER_LITERAL: return parse_number_literal();

  case TokenKind::STRING_LITERAL: return parse_string_literal();

  case TokenKind::IDENTIFIER: return parse_identifier();

  case TokenKind::TRUE_KEYWORD:
  case TokenKind::FALSE_KEYWORD: return parse_bool_literal();

  case TokenKind::OPEN_PAREN: return parse_grouped_expression();

  case TokenKind::OPEN_BRACE: return parse_object_literal();

  case TokenKind::OPEN_BRACKET: return parse_array_literal();

  default: return nullptr;
  }
}