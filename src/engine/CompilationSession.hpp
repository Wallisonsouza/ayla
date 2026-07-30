#pragma once

#include "core/managers/source_manager.hpp"

#include "core/visitor/Pipeline.hpp"

#include "engine/CompilerEnvironment.hpp"

#include "engine/UnitManager.hpp"

class CompilationSession {

public:
  CompilationSession() = default;
 Pipeline pipeline;
  CompilationUnit *add_script(const std::string &path) {
    auto *source = sources.create_source(path);

    return units.create(*source);
  }

  void compile() {
    for (auto &unit : units.all()) { pipeline.run(environment_,*unit); }
  }

  CompilerEnvironment &environment() { return environment_; }

private:
  CompilerEnvironment environment_;

  SourceManager sources;

  UnitManager units;

 
};