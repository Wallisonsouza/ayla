#include "core/visitor/Stage.hpp"
#include "debug/ast/AstDumper.hpp"

class DumperStage : public Stage {
  void run(CompilationUnit &unit) override {

    AstDumper dumper;
    dumper.run(unit);
  };
};