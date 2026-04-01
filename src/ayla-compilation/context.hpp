#pragma once
#include "core/module/module_manager.hpp"
#include "core/module/scope.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"
#include "language/BackendRegistry.hpp"

namespace ayla::compilation {
struct Context {

  core::table::DescriptorTable descriptor_table;
  core::table::PrecedenceTable precedence_table;
  core::ModuleManager module_manager;
  core::ParserScope root_scope;
  BackendRegistry backends;

  Context() : root_scope(nullptr) {}
};
} // namespace ayla::compilation
