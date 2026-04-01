#pragma once

#include "ayla-compilation/unit.hpp"
#include "ayla-source/source.hpp"
#include "ayla-source/source_stream.hpp"
#include "ayla-structural/ayla-token/token.hpp"

#include "utils/Unicode.hpp"

namespace ayla::syntax {
struct Lexer {
private:
  ayla::compilation::Unit &unit;
  source::SourceStream stream;

  ayla::structural::token::Token *match_token() {

    if (auto t = match_string()) return t;

    if (auto t = match_number()) return t;

    if (auto t = match_identifier()) return t;

    if (auto t = match_operator()) return t;

    return nullptr;
  }

public:
  Lexer(ayla::compilation::Unit &unit) : unit(unit), stream(unit.source.buffer) {};

  ayla::structural::token::Token *match_identifier();
  ayla::structural::token::Token *match_string();
  ayla::structural::token::Token *match_number();
  ayla::structural::token::Token *match_operator();
  ayla::structural::token::Token mathch_comment();

  void skip_whitespace_and_comments(source::SourceStream &stream) {
    while (!stream.eof()) {
      char32_t c = stream.peek();

      // Espaços em branco, mas NÃO newline
      if (utils::Unicode::is_white_space(c) && c != U'\n') {
        stream.advance();
        continue;
      }

      // Comentário de linha //
      if (c == U'/' && stream.peek_n(1) == U'/') {
        stream.advance_n(2);
        while (stream.peek() != U'\n' && !stream.eof()) stream.advance();
        continue;
      }

      // Comentário de bloco /* ... */
      if (c == U'/' && stream.peek_n(1) == U'*') {
        stream.advance_n(2);
        while (!stream.eof()) {
          if (stream.peek() == U'*' && stream.peek_n(1) == U'/') {
            stream.advance_n(2);
            break;
          }
          stream.advance();
        }
        continue;
      }

      break; // Não é espaço nem comentário
    }
  }

  void generate_tokens() {

    while (!stream.eof()) {
      skip_whitespace_and_comments(stream);

      if (stream.peek() == U'\n') {

        auto state = stream.get_state();

        auto desc = unit.context.descriptor_table.lookup_by_kind(ayla::structural::token::TokenKind::NEW_LINE);
        unit.tokens.create_token<ayla::structural::token::Token>(desc, stream.slice_from(state));
      }

      auto start_state = stream.get_state();
      auto *token = match_token();

      if (!token) {
        auto slice = source::SourceSlice{.range = start_state.range_to(stream.get_state()), .span = start_state.view_to(stream.get_state())};
        // unit.diagnostics.emit({DiagnosticCode::Unexpectedayla::structural::token::Token, slice},
        // unit);
        stream.advance();
      }
    }
  }
};

} // namespace ayla::syntax
