#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/core/visitor/Stage.hpp"
#include "celestia/debug/ast/AstDumper.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/ir/IR.hpp"

class IRStage : public Stage {
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    celestia::debug::AstDumper dumper;

    celestia::ir::IRContext context;
    

    dumper.dispatch(unit.ast_module);
  };
};