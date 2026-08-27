#pragma once
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/core/visitor/Stage.hpp"
#include "celestia/semantic/resolver/Resolver.hpp"

class ResolverStage : public Stage{

  void run(CompilerEnvironment &env, CompilationUnit &unit) override {


    celestia::semantic::ResolverContext ctx = celestia::semantic::ResolverContext(env, unit);

    celestia::semantic::Resolver resolver = celestia::semantic::Resolver(ctx);

    resolver.resolve(unit.ast_module);
  }
};