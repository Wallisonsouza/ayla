#pragma once

#include <string_view>

namespace ayla::source {

struct SourceSpan {
  const char *begin;
  const char *end;

  std::string_view view() const { return std::string_view(begin, end - begin); }
};

} // namespace ayla::source
