#include "lexer.hpp"

ayla::structural::token::Token *ayla::syntax::Lexer::match_operator() {
  auto start = stream.get_state();

  const auto *node = unit.context.descriptor_table.trie().root();
  const ayla::structural::token::TokenDescriptor *best = nullptr;
  size_t best_len = 0;

  size_t offset = 0;

  while (true) {
    char32_t c = stream.peek_n(offset);
    if (!c) break;

    node = node->child(c);
    if (!node) break;

    offset++;

    if (node->is_terminal) {
      best = node->value;
      best_len = offset;
    }
  }

  if (!best) return nullptr;

  stream.advance_n(best_len);
  auto slice = stream.slice_from(start);

  return unit.tokens.create_token<ayla::structural::token::Token>(best, slice);
}
