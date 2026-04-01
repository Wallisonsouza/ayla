#pragma once

#include "source_loader.hpp"
#include <cassert>
#include <string_view>

namespace ayla::source {

struct SourceLocation {
  size_t offset;
  size_t line;
  size_t column;
};

struct SourceRange {
  SourceLocation begin;
  SourceLocation end;
};

struct SourceSlice {
  SourceRange range;
  std::string_view span;
};

} // namespace ayla::source
