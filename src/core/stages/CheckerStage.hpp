#pragma once

#include "core/visitor/AstStage.hpp"
#include "semantic/resolver/Resolver.hpp"

class ResolverStage : public AstStage {

  void run(CompilationUnit &unit) override {

    Resolver resolver = Resolver(unit, nullptr);

    resolver.resolve(unit.ast.get_root());
  }
};