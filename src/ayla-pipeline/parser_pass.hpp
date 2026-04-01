#pragma once

#include "ayla-pipeline/pass.hpp"
#include "ayla-syntax/ayla-parser/parser.hpp"

struct ParsePass : Pass {
  void run(ayla::compilation::Unit &unit) override {
    Parser parser(unit);
    parser.parse_program();
  }
};