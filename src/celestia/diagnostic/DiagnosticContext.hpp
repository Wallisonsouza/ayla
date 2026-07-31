#pragma once

#include "celestia/diagnostic/Diagnostic.hpp"

#include <vector>

namespace diagnostic {

class DiagnosticContext {
public:
  void report(Diagnostic diagnostic) { diagnostics.push_back(std::move(diagnostic)); }

  bool has_errors() const {
    for (const auto &diag : diagnostics) {
      if (diag.severity == Severity::Error) return true;
    }

    return false;
  }

  const std::vector<Diagnostic> &all() const { return diagnostics; }

private:
  std::vector<Diagnostic> diagnostics;
};

} // namespace diagnostic