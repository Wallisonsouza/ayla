#pragma once

#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/core/visitor/Stage.hpp"
#include "celestia/semantic/checker/TypeChecker.hpp"
#include "celestia/semantic/resolver/Resolver.hpp"

class CheckStage : public Stage {

  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    celestia::semantic::ResolverContext ctx(env, unit);

    celestia::semantic::TypeChecker checker(ctx);

    checker.check(unit.ast_module);
  }
};