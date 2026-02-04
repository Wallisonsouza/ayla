#pragma once
#include "core/module/module_manager.hpp"
#include "core/module/scope.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"
#include "language/BackendRegistry.hpp"

struct LanguageContext {
  
  core::table::DescriptorTable descriptor_table;
  core::table::PrecedenceTable precedence_table;
  core::ModuleManager module_manager;
  core::ParserScope root_scope;
  BackendRegistry backends;

  LanguageContext() : root_scope(nullptr) {}
};
