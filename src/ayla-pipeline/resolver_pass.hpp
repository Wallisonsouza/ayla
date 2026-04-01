#pragma once

#include "ayla-compilation/unit.hpp"
#include "ayla-pipeline/pass.hpp"
#include "ayla-semantic/ayla-resolver/Resolver.hpp"

struct ResolvePass : Pass {
  void run(ayla::compilation::Unit &unit) override {
    Resolver resolver(unit, &unit.context.root_scope);

    for (auto &node : unit.ast.get_nodes()) resolver.resolve(node);
  }
};