#include "ayla/source/source_buffer.hpp"

#include <cassert>

namespace ayla::source {

SourceBuffer::SourceBuffer(std::string_view src) : data(src) {
  size_t start = 0;
  while (start < data.size()) {
    size_t end = data.find('\n', start);
    if (end == std::string::npos) end = data.size();

    lines.push_back(std::string_view(data.data() + start, end - start));
    start = end + 1;
  }
}

const char *SourceBuffer::begin() const { return data.data(); }

const char *SourceBuffer::end() const { return data.data() + data.size(); }

size_t SourceBuffer::size() const { return data.size(); }

std::string_view SourceBuffer::view() const { return {data.data(), data.size()}; }

std::string_view SourceBuffer::get_line(size_t line_number) const {
  if (line_number == 0 || line_number > lines.size()) return {};
  return lines[line_number - 1];
}

std::string SourceBuffer::get_text(const SourceSpan &span) const {
  assert(span.begin >= data.data() && span.end <= data.data() + data.size());
  return std::string(span.begin, span.end);
}

const char *SourceBuffer::line_begin(size_t line_number) const {
  if (line_number == 0 || line_number > lines.size()) return nullptr;
  return lines[line_number - 1].data();
}

size_t SourceBuffer::line_count() const { return lines.size(); }

} // namespace ayla::source