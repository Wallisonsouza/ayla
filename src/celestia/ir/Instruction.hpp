#pragma once

#include "celestia/ir/InstructionKind.hpp"
#include "celestia/ir/IRIds.hpp"
#include <string>
#include <variant>

namespace celestia::ir {

struct Instruction {
  InstructionId id;
  InstructionKind kind;

  ValueId result = ValueId::invalid();

  std::vector<ValueId> operands;

  std::variant<
      std::monostate,
      bool,
      char,
      int64_t,
      uint64_t,
      float,
      double,
      std::string
  > data;
};

} // namespace celestia::ir