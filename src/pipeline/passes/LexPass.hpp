#pragma once

#include "ayla/syntax/lexer/lexer.hpp"
#include "pipeline/Pass.hpp"

struct LexPass : Pass {
  void run(CompilationUnit &unit) override {
    ayla::syntax::Lexer lexer(unit);
    lexer.generate_tokens();
  }
};
