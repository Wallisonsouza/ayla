#pragma once
#include "ayla-source/source.hpp"
#include "utils/Utf8.hpp"
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

namespace ayla::source {

class SourceStream {
public:
  struct State {
    const char *ptr;
    size_t offset;
    size_t line;
    size_t column;

    std::string_view view_to(const State &end) const { return std::string_view(ptr, end.ptr - ptr); }

    ayla::source::SourceRange range_to(const State &end) const { return ayla::source::SourceRange{.begin = {offset, line, column}, .end = {end.offset, end.line, end.column}}; }
  };

private:
  const ayla::source::SourceBuffer &buffer;
  const char *begin;
  const char *current;
  const char *end;

  size_t line = 1;
  size_t column = 1;

  std::vector<State> checkpoints;

public:
  explicit SourceStream(const ayla::source::SourceBuffer &buf) : buffer(buf), begin(buf.begin()), current(buf.begin()), end(buf.end()) {}

  bool eof() const { return current >= end; }

  char32_t peek() const {
    if (eof()) return U'\0';
    size_t len = utils::Utf::utf8_char_len(static_cast<uint8_t>(*current));
    return utils::Utf::utf8_to_codepoint(current, len);
  }

  char32_t peek_n(size_t n) const {
    const char *p = current;
    while (n--) {
      if (p >= buffer.end()) return 0;
      size_t len = utils::Utf::utf8_char_len(static_cast<uint8_t>(*p));
      p += len;
    }
    if (p >= buffer.end()) return 0;
    size_t len = utils::Utf::utf8_char_len(static_cast<uint8_t>(*p));
    return utils::Utf::utf8_to_codepoint(p, len);
  }

  char32_t advance() {
    if (eof()) return U'\0';
    size_t len = utils::Utf::utf8_char_len(static_cast<uint8_t>(*current));
    char32_t cp = utils::Utf::utf8_to_codepoint(current, len);

    current += len;
    if (cp == U'\n') {
      line++;
      column = 1; // opcional, só para info
    } else {
      column++; // apenas contador simples (opcional)
    }

    return cp;
  }

  void advance_n(size_t n) {
    while (n--) advance();
  }

  ayla::source::SourceSlice slice_from(const State &start) const {
    State end_state = get_state();
    return {.range = start.range_to(end_state), .span = start.view_to(end_state)};
  }

  const char *mark() const { return current; }

  State get_state() const { return {current, static_cast<size_t>(current - begin), line, column}; }

  void rollback(const State &s) {
    current = s.ptr;
    line = s.line;
    column = s.column;
  }

  void push_checkpoint() { checkpoints.push_back(get_state()); }
  void rollback_checkpoint() {
    if (!checkpoints.empty()) {
      rollback(checkpoints.back());
      checkpoints.pop_back();
    }
  }
  void discard_checkpoint() {
    if (!checkpoints.empty()) checkpoints.pop_back();
  }

  // template <typename Predicate> size_t advance_while(Predicate pred) {
  //   size_t count = 0;
  //   while (!eof()) {
  //     size_t len = utils::Utf::utf8_char_len(static_cast<uint8_t>(*current));
  //     char32_t cp = utils::Utf::utf8_to_codepoint(current, len);
  //     if (!pred(cp)) break;
  //     current += len;
  //     if (cp == U'\n') {
  //       line++;
  //       column = 1;
  //     } else {
  //       column++;
  //     }
  //     count++;
  //   }
  //   return count;
  // }
};

} // namespace ayla::source
