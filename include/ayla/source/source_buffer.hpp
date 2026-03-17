#pragma once

#include "ayla/source/source_span.hpp"

#include <string>
#include <string_view>
#include <vector>

namespace ayla::source {

class SourceBuffer {
  std::string data;
  std::vector<std::string_view> lines;

public:
  explicit SourceBuffer(std::string_view src);

  const char *begin() const;
  const char *end() const;
  size_t size() const;
  std::string_view view() const;

  std::string_view get_line(size_t line_number) const;

  std::string get_text(const ayla::source::SourceSpan &span) const;

  const char *line_begin(size_t line_number) const;

  size_t line_count() const;
};

} // namespace ayla::source