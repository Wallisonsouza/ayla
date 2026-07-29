#include "core/visitor/Stage.hpp"
#include "debug/ast/AstDumper.hpp"

class AstDumperStage : public Stage {
  void run(CompilationUnit &unit) override {

    AstDumper dumper;
    dumper.run(unit);
  };
};