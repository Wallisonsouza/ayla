#include "celestia/core/visitor/Stage.hpp"

#include "celestia/debug/lexer/TokenDumper.hpp"
#include "celestia/engine/CompilationUnit.hpp"
#include "celestia/engine/CompilerEnvironment.hpp"
#include <iostream>

class TokenDumperStage : public Stage {
  void run(CompilerEnvironment& env, CompilationUnit &unit) override {

    debug::lexer::TokenDumper dumper;
    std::cout << dumper.dump(unit.tokens, unit.source.buffer);
  };
};