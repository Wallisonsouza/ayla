
#pragma once

#include "pipeline/Pass.hpp"
#include "semantic/checker/type_checker.hpp"

struct CheckPass : Pass {
  void run(CompilationUnit &unit) override {
    ayla::Checker checker(unit);

    for (auto &node : unit.ast.get_nodes()) checker.check(node);
  }
};
