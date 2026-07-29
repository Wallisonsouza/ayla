#pragma once

#include "diagnostic/DiagnosticCode.hpp"

#include <string_view>

namespace diagnostic {

struct DiagnosticTemplate {
  std::string_view title;

  std::string_view message;

  std::string_view label;

  std::string_view help;
};

const DiagnosticTemplate &get_template(DiagnosticCode code);

} // namespace diagnostic