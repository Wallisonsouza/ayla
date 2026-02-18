
#pragma once

#include "pipeline/Pass.hpp"
#include "semantic/checker/TypeChecker.hpp"

struct CheckPass : Pass {
  void run(CompilationUnit &unit) override {
    ayla::TypeChecker checker(unit);

    for (auto &node : unit.ast.get_nodes()) checker.check(node);
  }
};
