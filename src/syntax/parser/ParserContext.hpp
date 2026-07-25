#pragma once

#include "engine/CompilationUnit.hpp"

class ParseContext {
public:
  CompilationUnit &unit;

  explicit ParseContext(CompilationUnit &unit) : unit(unit) {}

  auto &tokens() { return unit.tokens; }

  auto &source() { return unit.source; }

  auto &ast() { return unit.ast; }

  auto &precedence() { return unit.context.precedence_table; }

  auto &diagnostics() { return unit.diagns; }

  void report_error(DiagnosticCode code) {}

  auto &descriptors() { return unit.context.descriptor_table; }
};