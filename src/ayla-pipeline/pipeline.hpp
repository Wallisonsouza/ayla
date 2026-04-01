
#pragma once

#include "ayla-pipeline/pass.hpp"
#include <memory>
#include <vector>

struct Pipeline {
  std::vector<std::unique_ptr<Pass>> passes;

  void add_pass(std::unique_ptr<Pass> pass) { passes.push_back(std::move(pass)); }

  void run(ayla::compilation::Unit &unit) {
    for (auto &pass : passes) pass->run(unit);
  }
};