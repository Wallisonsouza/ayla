#pragma once

#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/core/visitor/Pipeline.hpp"
#include "celestia/diagnostic/diagnostic_debug.hpp"

#include <string>
#include <vector>

class Compiler;

class CompilationFrame {
public:
  CompilationFrame(Compiler &compiler) : compiler_(compiler) {}

  CompilationFrame &add_script(const std::string &path);

  template <typename Stage> CompilationFrame &add_stage() {
    pipeline_.add_stage<Stage>();
    return *this;
  }

  void run();


  std::vector<CompilationUnit *> units_;

private:
  Compiler &compiler_;

  Pipeline pipeline_;
};