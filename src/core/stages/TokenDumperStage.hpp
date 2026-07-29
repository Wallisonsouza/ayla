#include "core/visitor/Stage.hpp"

#include "debug/lexer/TokenDumper.hpp"
#include "engine/CompilationUnit.hpp"
#include <iostream>

class TokenDumperStage : public Stage {
  void run(CompilationUnit &unit) override {

    debug::lexer::TokenDumper dumper;
    std::cout << dumper.dump(unit.tokens, unit.source.buffer);
  };
};