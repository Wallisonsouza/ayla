#pragma once

#include <vector>

#include "celestia/ir/IRIds.hpp"

namespace celestia::ir {

struct Value {
  ValueId id;
  TypeId type;
};

struct StructField {
  StringId name;
  TypeId type;
};

struct Struct {
  StructId id;
  StringId name;
  std::vector<StructField> fields;
};

struct InterfaceMethod {
  StringId name;
  TypeId type;
};

struct Interface {
  InterfaceId id;
  StringId name;
  std::vector<InterfaceMethod> methods;
};


struct VTable {
  VTableId id;
  InterfaceId interface_id;
  StructId concrete_type;

  std::vector<FunctionId> methods;
};

} // namespace celestia::ir
