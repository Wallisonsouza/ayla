#pragma once

#include <cstdint>

namespace celestia::ir {

enum class InstructionKind : uint8_t {
  Constant,

  Add,
  Sub,
  Mul,
  Div,
  MakeInterface,
  InterfaceCall,

  Return,
};
} // namespace celestia::ir