#pragma once
#include "ayla-syntax/ayla-parser/scope.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"

namespace ayla::compilation {
struct Context {

  core::table::DescriptorTable descriptor_table;
  core::table::PrecedenceTable precedence_table;
  core::ParserScope root_scope;
  Context() : root_scope(nullptr) {}
};
} // namespace ayla::compilation
