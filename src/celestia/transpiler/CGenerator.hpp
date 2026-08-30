#pragma once

#include "celestia/ir/IR.hpp"
#include "celestia/ir/IRIds.hpp"

#include <ostream>

namespace celestia::codegen {

class CGenerator {
public:
  CGenerator(std::ostream &out, ir::IRContext &ir)
      : out(out), ir(ir) {}

  void generate();

private:
  void generate_struct(ir::StructId id);
  void generate_type(ir::TypeId id);
  void generate_value(ir::ValueId id);
  void generate_instruction(const ir::Instruction &instruction);

private:
  std::ostream &out;
  ir::IRContext &ir;
};

} // namespace celestia::codegen