#include "celestia/core/visitor/Stage.hpp"

#include "celestia/debug/lexer/TokenDumper.hpp"
#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include <iostream>

class TokenDumperStage : public Stage {
  void run(CompilerEnvironment& env, CompilationUnit &unit) override {

    celestia::debug::TokenDumper dumper;
    std::cout << dumper.dump(unit.tokens, unit.source.buffer);
  };
};