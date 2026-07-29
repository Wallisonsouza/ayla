#pragma once

#include "diagnostic/DiagnosticCode.hpp"
#include "engine/CompilationUnit.hpp"

class ParseContext {
public:
  CompilationUnit &unit;

  explicit ParseContext(CompilationUnit &unit) : unit(unit) {}

  auto &tokens() { return unit.tokens; }

  auto &source() { return unit.source; }

  auto &ast() { return unit.ast; }

  auto &operators() { return unit.context.operators; }

  auto &diagnostics() { return unit.diags; }

  void report_error(diagnostic::DiagnosticCode code) {}

  auto &descriptors() { return unit.context.descriptors; }
};