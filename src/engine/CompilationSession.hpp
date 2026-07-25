#pragma once

#include "core/managers/source_manager.hpp"
#include "core/visitor/PassManager.hpp"
#include "core/visitor/Pipeline.hpp"
#include "engine/LangContext.hpp"
#include "engine/UnitManager.hpp"
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

private:
  void compile_unit(CompilationUnit &unit) { pipeline_.run(unit); }

private:
  LanguageContext &context;

  SourceManager sources;

  UnitManager units;

  Pipeline pipeline_;
};