#include "ayla-syntax/ayla-parser/parser.hpp"

core::ast::ASTExpressionNode *Parser::parse_primary_expression() {

  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  switch (tok->descriptor->kind) {

  case ayla::structural::token::TokenKind::NUMBER_LITERAL: return parse_number_literal();

  case ayla::structural::token::TokenKind::STRING_LITERAL: return parse_string_literal();

  case ayla::structural::token::TokenKind::IDENTIFIER: return parse_identifier();

  case ayla::structural::token::TokenKind::OPEN_PAREN: return parse_grouped_expression();

  case ayla::structural::token::TokenKind::OPEN_BRACE: return parse_object_literal();

  case ayla::structural::token::TokenKind::OPEN_BRACKET: return parse_array_literal();

  default: return nullptr;
  }
}