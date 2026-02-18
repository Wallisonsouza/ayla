#pragma once

#include "pipeline/Pass.hpp"
#include "syntax/lexer/lexer.hpp"

struct LexPass : Pass {
  void run(CompilationUnit &unit) override {
    Lexer lexer(unit);
    lexer.generate_tokens();
  }
};
