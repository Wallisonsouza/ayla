
#pragma once

#include "Pass.hpp"
#include <memory>
#include <vector>

struct Pipeline {
  std::vector<std::unique_ptr<Pass>> passes;

  void add_pass(std::unique_ptr<Pass> pass) { passes.push_back(std::move(pass)); }

  void run(CompilationUnit &unit) {
    for (auto &pass : passes) pass->run();
  }
};