#pragma once

#include "core/managers/source_manager.hpp"
#include "core/visitor/PassManager.hpp"
#include "core/visitor/Pipeline.hpp"
#include "diagnostic/diagnostic_debug.hpp"
#include "engine/LangContext.hpp"
#include "engine/UnitManager.hpp"
#include <iostream>


class CompilationSession {

public:
  explicit CompilationSession(LanguageContext &context) : context(context) {}

  CompilationUnit *add_script(const std::string &path) {
    auto *source = sources.create_source(path);

    return units.create_compilation_unit(context, *source);
  }

  void compile() {
    for (auto &unit : units.units) { compile_unit(*unit); }
  }

  Pipeline &pipeline() { return pipeline_; }

  void show_diagnostics() {

    for (auto &unit : units.units) { 

      std::cout << unit->source.path << ":" << std::endl;

      for (auto &diag : unit->diags.all()) {
      //  diagnostic::print_diagnostic(diag, unit->source);
      }
      
    }
  }

private:
  void compile_unit(CompilationUnit &unit) { pipeline_.run(unit); }

private:
  LanguageContext &context;

  SourceManager sources;

  UnitManager units;

  Pipeline pipeline_;
};