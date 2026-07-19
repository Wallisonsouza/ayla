#pragma once

#include "engine/CompilationUnit.hpp"

struct Pass {
  virtual ~Pass() = default;
  public:
  virtual void run(CompilationUnit &unit) = 0;
};