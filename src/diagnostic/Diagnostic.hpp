#pragma once

#include "diagnostic/DiagnosticCode.hpp"
#include "diagnostic/Expected.hpp"
#include "diagnostic/Label.hpp"
#include "diagnostic/Severity.hpp"

#include <string>
#include <vector>

#pragma once

namespace diagnostic {

struct Diagnostic {
  Severity severity;

  DiagnosticCode code;

  std::optional<Expected> expected;

  std::optional<Found> found;

  std::vector<Label> labels;

  std::vector<std::string> helps;

  std::vector<std::string> notes;
};

} // namespace diagnostic