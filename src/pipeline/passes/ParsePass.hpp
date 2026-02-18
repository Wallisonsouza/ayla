#pragma once

#include "pipeline/Pass.hpp"
#include "syntax/parser/parser.hpp"

struct ParsePass : Pass {
  void run(CompilationUnit &unit) override {
    Parser parser(unit);
    parser.parse_program();
  }
};
