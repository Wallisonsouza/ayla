#pragma once

#include "celestia/engine/CompilerEnvironment.hpp"
class CompilationUnit;

class Stage {
public:
  virtual ~Stage() = default;

  virtual void run(CompilerEnvironment &env, CompilationUnit &unit) = 0;
};