#pragma once

#include "core/token/Location.hpp"

namespace diagnostic {

enum class LabelKind {
  Primary,

  Secondary
};

struct Label {
  SourceSlice slice;

  LabelKind kind;
};
}