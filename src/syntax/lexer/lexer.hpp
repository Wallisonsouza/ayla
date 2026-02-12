#pragma once

#include "core/source/TextStream.hpp"
#include "core/token/Token.hpp"
#include "engine/CompilationUnit.hpp"
#include "utils/Unicode.hpp"

struct Lexer {
private:
  CompilationUnit &unit;
  core::source::TextStream stream;

  Token *match_token() {

    if (auto t = match_string())
      return t;

    if (auto t = match_number())
      return t;

    if (auto t = match_identifier())
      return t;

    if (auto t = match_operator())
      return t;

    return nullptr;
  }

public:
  Lexer(CompilationUnit &unit) : unit(unit), stream(unit.source.buffer) {};

  Token *match_identifier();
  Token *match_string();
  Token *match_number();
  Token *match_operator();
  Token mathch_comment();

  void skip_whitespace_and_comments(core::source::TextStream &stream) {
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
        while (stream.peek() != U'\n' && !stream.eof())
          stream.advance();
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

        auto desc =
            unit.context.descriptor_table.lookup_by_kind(TokenKind::NEW_LINE);
        unit.tokens.create_token<Token>(desc, stream.slice_from(state));
      }

      auto start_state = stream.get_state();
      auto *token = match_token();

      if (!token) {
        auto slice =
            SourceSlice{.range = start_state.range_to(stream.get_state()),
                        .span = start_state.span_to(stream.get_state())};
        // unit.diagnostics.emit({DiagnosticCode::UnexpectedToken, slice},
        // unit);
        stream.advance();
      }
    }
  }
};
