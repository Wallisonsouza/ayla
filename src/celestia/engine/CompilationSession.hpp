#pragma once

#include "celestia/core/managers/source_manager.hpp"

#include "celestia/core/visitor/Pipeline.hpp"

#include "celestia/diagnostic/diagnostic_debug.hpp"
#include "celestia/engine/CompilerEnvironment.hpp"

#include "celestia/engine/UnitManager.hpp"

class CompilationSession {

public:
  CompilationSession() = default;
  Pipeline pipeline;
  CompilationUnit *add_script(const std::string &path) {
    auto *source = sources.create_source(path);

    return units.create(*source);
  }

  void compile() {
    for (auto &unit : units.all()) { pipeline.run(environment_, *unit); }
  }

  void diagnostics() {
    for (auto &unit : units.all()) {

      for (auto &diag : unit->diagnostics.all()) {
          diagnostic::print_diagnostic(diag, unit->source);
      }
    }
  }

  CompilerEnvironment &environment() { return environment_; }

private:
  CompilerEnvironment environment_;

  SourceManager sources;

  UnitManager units;
};