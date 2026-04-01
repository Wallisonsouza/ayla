#pragma once

#include "ayla-compilation/unit.hpp"

struct Pass {
  virtual ~Pass() = default;
  virtual void run(ayla::compilation::Unit &unit) = 0;
};