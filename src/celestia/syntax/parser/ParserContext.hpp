#pragma once

#include "celestia/diagnostic/Diagnostic.hpp"
#include "celestia/diagnostic/DiagnosticCode.hpp"
#include "celestia/engine/CompilationUnit.hpp"
#include "celestia/engine/CompilerEnvironment.hpp"

class ParseContext {
public:
  CompilationUnit &unit;
  CompilerEnvironment &env;

  explicit ParseContext(CompilationUnit &unit, CompilerEnvironment &e) : unit(unit), env(e) {}

  auto &tokens() { return unit.tokens; }

  auto &source() { return unit.source; }

  auto &get_ast() { return unit.ast; }

  auto &operators() { return env.language.operators; }

  auto &diagnostics() { return unit.diagnostics; }

  void report_error(diagnostic::Diagnostic diag) {unit.diagnostics.report(diag);}

  auto &descriptors() { return env.language.descriptors; }
};