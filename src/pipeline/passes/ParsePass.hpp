#pragma once

#include "ayla/syntax/parser/parser.hpp"
#include "pipeline/Pass.hpp"

struct ParsePass : Pass {
  void run(CompilationUnit &unit) override {
    ayla::syntax::Parser parser(unit);
    parser.parse_program();
  }
};
