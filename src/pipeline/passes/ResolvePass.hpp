#pragma once

#include "pipeline/Pass.hpp"
#include "semantic/resolver/Resolver.hpp"

struct ResolvePass : Pass {
  void run(CompilationUnit &unit) override {
    Resolver resolver(unit, &unit.context.root_scope);

    for (auto &node : unit.ast.get_nodes()) resolver.resolve(node);
  }
};
