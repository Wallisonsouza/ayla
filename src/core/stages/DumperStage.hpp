#include "core/visitor/Stage.hpp"
#include "debug/ast/AstDumper.hpp"
#include "engine/CompilerEnvironment.hpp"

class AstDumperStage : public Stage {
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    AstDumper dumper;
    dumper.run(env,unit);
  };
};