#pragma once

#include "celestia/ir/IRIds.hpp"
#include <string>
#include <vector>

namespace celestia::ir {

struct Module {
  ModuleId id;

  std::string name;

  std::vector<FunctionId> functions;
};

} // namespace celestia::ir