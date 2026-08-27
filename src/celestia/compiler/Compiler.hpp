#pragma once

#include "celestia/compiler/CompilationFrame.hpp"
#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/compiler/UnitManager.hpp"
#include "celestia/core/managers/source_manager.hpp"
#include "celestia/diagnostic/diagnostic_debug.hpp"
#include "celestia/language/LanguageDefinition.hpp"


class Compiler {
public:
  Compiler(celestia::LanguageDefinition &lang) { environment_.language = lang; }

  CompilationFrame create_frame() { return CompilationFrame(*this); }

  CompilationUnit *add_script(const std::string &path) {
    auto *source = sources.create_source(path);
    return units.create(*source);
  }
 
  CompilerEnvironment &environment() { return environment_; }

private:
  friend class CompilationFrame;

  CompilerEnvironment environment_;

  SourceManager sources;
  UnitManager units;
};