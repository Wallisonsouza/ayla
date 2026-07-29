#pragma once

#include "DiagnosticTemplate.hpp"
#include "DiagnosticCode.hpp"

namespace diagnostic {

inline const DiagnosticTemplate &get_template(DiagnosticCode code) {
  static const DiagnosticTemplate expected_pattern{.title = "expected pattern",

                                                   .message = "expected a pattern, found '{}'",

                                                   .help = "provide a valid pattern"};

  static const DiagnosticTemplate expected_expression{.title = "expected expression",

                                                      .message = "expected expression, found '{}'",

                                                      .help = "add an expression here"};

  switch (code) {
  case DiagnosticCode::ExpectedPattern: return expected_pattern;

  case DiagnosticCode::ExpectedExpression: return expected_expression;
  }

  return expected_pattern;
}

} // namespace diagnostic