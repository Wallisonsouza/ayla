#include "lexer.hpp"

Token *Lexer::match_identifier() {

  auto start = stream.get_state();
  char32_t c = stream.peek();

  if (!utils::Unicode::is_alpha(c) && c != U'_') return nullptr;

  stream.advance();

  while (true) {
    c = stream.peek();
    if (utils::Unicode::is_alpha(c) || utils::Unicode::is_digit(c) || c == U'_') {
      stream.advance();
    } else {
      break;
    }
  }

  auto slice = stream.slice_from(start);

  auto descriptor = unit.context.descriptor_table.lookup_by_name(slice.span.view());
  if (!descriptor) { descriptor = unit.context.descriptor_table.lookup_by_kind(TokenKind::IDENTIFIER); }

  return unit.tokens.create_token<Token>(descriptor, slice);
}
