#include "celestia/core/visitor/Stage.hpp"
#include "celestia/debug/ast/AstDumper.hpp"
#include "celestia/engine/CompilerEnvironment.hpp"

class AstDumperStage : public Stage {
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    AstDumper dumper;
    dumper.run(env,unit);
  };
};