#include "MarkerBuilder.hpp"

#include "celestia/utils/Unicode.hpp"
#include "celestia/utils/Utf8.hpp"

namespace diagnostic {

std::string MarkerBuilder::underline(const LineCut &cut, const core::source::Span &span, std::string_view fill, std::string_view mark) {
  std::string out;

  const char *p = cut.start;

  const char *span_begin = source.begin() + span.begin;

  const char *span_end = source.begin() + span.end;

  while (p < cut.end) {
    auto result = utils::Utf8::decode(p);

    int width = utils::Unicode::char_width(result.codepoint);

    if (p >= span_begin && p < span_end) {
      for (int i = 0; i < width; ++i) out += mark;
    } else {
      for (int i = 0; i < width; ++i) out += fill;
    }

    p += result.size;
  }

  return std::string(cut.prefix_offset, ' ') + out;
}

std::string MarkerBuilder::caret(const LineCut &cut, const core::source::Span &span) {
  const char *span_end = source.begin() + span.end;

  int position = static_cast<int>(span_end - cut.start) + cut.prefix_offset - 1;

  if (position < 0) position = 0;

  std::string out(position, ' ');

  out += '^';

  return out;
}

} // namespace diagnostic