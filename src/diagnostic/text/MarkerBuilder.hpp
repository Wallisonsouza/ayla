#pragma once

#include "core/source/SourceBuffer.hpp"
#include "core/source/Span.hpp"

#include "diagnostic/text/LineCutter.hpp"

#include <string>
#include <string_view>

namespace diagnostic {

class MarkerBuilder {

private:
  const core::source::SourceBuffer &source;

public:
  explicit MarkerBuilder(const core::source::SourceBuffer &source) : source(source) {}

  std::string underline(const LineCut &cut, const core::source::Span &span, std::string_view fill = " ", std::string_view mark = "~");

  std::string caret(const LineCut &cut, const core::source::Span &span);
};

} // namespace diagnostic