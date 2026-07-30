#pragma once

#include "diagnostic/DiagnosticCode.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/CompilerEnvironment.hpp"

class ParseContext {
public:
  CompilationUnit &unit;
  CompilerEnvironment &env;

  explicit ParseContext(CompilationUnit &unit, CompilerEnvironment &e) : unit(unit), env(e) {}

  auto &tokens() { return unit.tokens; }

  auto &source() { return unit.source; }

  auto &ast() { return unit.ast; }

  auto &operators() { return env.language.operators; }

  auto &diagnostics() { return unit.diagnostics; }

  void report_error(diagnostic::DiagnosticCode code) {}

  auto &descriptors() { return env.language.descriptors; }
};