#pragma once

#include "pipeline/Pass.hpp"
#include "runtime/ByteCode.hpp"

struct ByteCodePass : Pass {

  void run(CompilationUnit &unit) override { unit.module = ayla::compiler::BytecodeGenerator::build(unit.ast.get_nodes()); }
};
