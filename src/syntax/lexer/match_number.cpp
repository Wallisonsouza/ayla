#include "lexer.hpp"

Token *Lexer::match_number() {

  auto start = stream.get_state();

  auto c = stream.peek();

  if (!utils::Unicode::is_digit(c)) { return nullptr; }

  bool has_dot = false;

  while (true) {
    c = stream.peek();
    if (utils::Unicode::is_digit(c)) {
      stream.advance();
    } else if (c == U'.' && !has_dot) {
      has_dot = true;
      stream.advance();
    } else {
      break;
    }
  }

  auto slice = stream.slice_from(start);

  auto descriptor = unit.context.descriptor_table.lookup_by_kind(TokenKind::NUMBER_LITERAL);

  return unit.tokens.create_token<Token>(descriptor, slice);
}
