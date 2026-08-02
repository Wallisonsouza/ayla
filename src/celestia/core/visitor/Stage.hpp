#pragma once

#include "celestia/compiler/CompilerEnvironment.hpp"
class CompilationUnit;

class Stage {
public:
  virtual ~Stage() = default;

  virtual void run(CompilerEnvironment &env, CompilationUnit &unit) = 0;
};