#pragma once

#include "core/source/Span.hpp"
#include <cassert>
#include <string>
#include <string_view>
#include <vector>

namespace core::source {

class SourceBuffer {
  std::string data;
  std::vector<std::string_view> lines;

public:
  explicit SourceBuffer(std::string_view src) : data(src) {
    size_t start = 0;

    while (start < data.size()) {
      size_t end = data.find('\n', start);

      if (end == std::string::npos) end = data.size();

      lines.emplace_back(data.data() + start, end - start);

      start = end + 1;
    }
  }

  const char *begin() const noexcept { return data.data(); }

  const char *end() const noexcept { return data.data() + data.size(); }

  size_t size() const noexcept { return data.size(); }

  std::string_view view() const noexcept { return data; }

  std::string_view get_line(size_t line_number) const {
    if (line_number == 0 || line_number > lines.size()) return {};

    return lines[line_number - 1];
  }

  std::string_view get_view(const Span &span) const noexcept {
    assert(span.begin <= span.end);
    assert(span.end <= data.size());

    return {data.data() + span.begin, span.end - span.begin};
  }

  std::string get_text(const Span &span) const {
    assert(span.begin <= span.end);
    assert(span.end <= data.size());

    return std::string(data.data() + span.begin, span.end - span.begin);
  }

  const char *line_begin(size_t line_number) const {
    if (line_number == 0 || line_number > lines.size()) return nullptr;

    return lines[line_number - 1].data();
  }

  size_t line_count() const noexcept { return lines.size(); }
};

} // namespace core::source