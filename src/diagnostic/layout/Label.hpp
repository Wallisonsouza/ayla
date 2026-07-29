#pragma once

#include "core/source/Span.hpp"

#include <string>

namespace diagnostic {

enum class LabelKind { Primary, Secondary };

struct Label {
  core::source::Span span;

  std::string message;

  LabelKind kind{LabelKind::Primary};
};

} // namespace diagnostic