#pragma once

#include "engine/CompilationUnit.hpp"

struct Pass {

  public:
    virtual ~Pass() = default;
  virtual void run(CompilationUnit &unit) = 0;
};