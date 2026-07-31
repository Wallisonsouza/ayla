#pragma once

#include "celestia/core/visitor/AstStage.hpp"
#include "celestia/engine/CompilerEnvironment.hpp"
#include "celestia/semantic/resolver/Resolver.hpp"

class ResolverStage : public AstStage {

  void run(CompilerEnvironment &env, CompilationUnit &unit) override {


    ResolverContext ctx = ResolverContext(env, unit);

    Resolver resolver = Resolver(ctx);

    resolver.resolve(unit.ast.get_root());
  }
};