#pragma once

#include <string>

#include "celestia/core/source/Source.hpp"
#include "celestia/core/token/Location.hpp"

namespace diagnostic {

struct LineCut {

  std::string text;

  const char *start{};

  const char *end{};

  int prefix_offset{};
};

class LineCutter {

public:

  LineCut cut(const core::source::Source &source, const SourceSlice &slice);

private:
  const char *compute_start(const char *line_begin, const char *span_begin);

  const char *compute_end(const char *line_end, const char *span_end);
};

} // namespace diagnostic