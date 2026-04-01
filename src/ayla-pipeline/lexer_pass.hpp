#pragma once

#include "ayla-compilation/unit.hpp"
#include "ayla-pipeline/pass.hpp"
#include "ayla-syntax/ayla-lexer/lexer.hpp"

struct LexerPass : Pass {
  void run(ayla::compilation::Unit &unit) override {
    Lexer lexer(unit);
    lexer.generate_tokens();
  }
};