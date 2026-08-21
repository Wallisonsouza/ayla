#pragma once

#include "celestia/core/visitor/AstStage.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/semantic/resolver/Resolver.hpp"

class ResolverStage : public AstStage {

  void run(CompilerEnvironment &env, CompilationUnit &unit) override {


    celestia::semantic::ResolverContext ctx = celestia::semantic::ResolverContext(env, unit);

    celestia::semantic::Resolver resolver = celestia::semantic::Resolver(ctx);

    resolver.resolve(unit.ast.get_root());
  }
};