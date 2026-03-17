#pragma once

#include "ayla/semantic/resolver/resolver.hpp"
#include "pipeline/Pass.hpp"

struct ResolvePass : Pass {
  void run(CompilationUnit &unit) override {
    ayla::semantic::Resolver resolver(unit, &unit.context.root_scope);

    for (auto &node : unit.ast.get_nodes()) resolver.resolve(node);
  }
};
