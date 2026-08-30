
#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/core/visitor/Stage.hpp"
#include "celestia/ir/IRDumper.hpp"
#include "celestia/lowering/Lowering.hpp"
#include <iostream>

class LoweringStage : public Stage {
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {


    celestia::lowering::LoweringContext lowering(unit.ir, env);

    celestia::ir::IRDumper dumper(unit.ir);

    lowering.lower(unit.ast_module);
    dumper.dump(std::cout);
  }
};