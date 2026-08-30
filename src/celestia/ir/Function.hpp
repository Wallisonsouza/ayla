#pragma once

#include <string>
#include <vector>

#include "celestia/ir/IRIds.hpp"

namespace celestia::ir {

struct Parameter {
  ValueId value;
  TypeId type;
};

struct Function {

  FunctionId id;

  std::string name;

  TypeId return_type;

  std::vector<Parameter> parameters;

  std::vector<BlockId> blocks;

  bool exported = false;
};

} // namespace celestia::ir