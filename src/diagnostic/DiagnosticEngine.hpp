#pragma once
#include "Diagnostic.hpp"
#include "core/memory/Arena.hpp"

#include <vector>

namespace ayla::compilation {
struct Unit;
}

class DiagnosticEngine {
  const ayla::compilation::Unit &unit;
  core::memory::Arena arena_;
  std::vector<Diagnostic *> diagnostics_;

public:
  explicit DiagnosticEngine(const ayla::compilation::Unit &unit) : unit(unit) {}

  Diagnostic *create(DiagnosticCode code, const ayla::source::SourceSlice &slice) {
    auto *diag = arena_.alloc<Diagnostic>();
    diag->origin = DiagnosticOrigin::Parser;
    diag->code = code;
    diag->slice = slice;
    diag->context = DiagnosticContext{};

    diagnostics_.push_back(diag);
    return diag;
  }

  const std::vector<Diagnostic *> &all() const { return diagnostics_; }
};
