#pragma once

#include <vector>

#include "celestia/ir/IRIds.hpp"

namespace celestia::ir {

struct Block {
  BlockId id;

  std::vector<InstructionId> instructions;
};

} // namespace celestia::ir