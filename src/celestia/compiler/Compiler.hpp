#pragma once

#include "celestia/core/managers/source_manager.hpp"

#include "celestia/core/visitor/Pipeline.hpp"

#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/diagnostic/diagnostic_debug.hpp"

#include "celestia/compiler/UnitManager.hpp"
#include "celestia/language/LanguageDefinition.hpp"

class Compiler {

public:
  Compiler(celestia::LanguageDefinition &lang) { environment_.language = lang; }
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

      for (auto &diag : unit->diagnostics.all()) { diagnostic::print_diagnostic(diag, unit->source); }
    }
  }

  CompilerEnvironment &environment() { return environment_; }

private:
  CompilerEnvironment environment_;

  SourceManager sources;

  UnitManager units;
};