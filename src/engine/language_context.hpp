#pragma once

#include "core/memory/Arena.hpp"
#include "core/module/module_manager.hpp"
#include "core/module/scope.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"
#include "frontend/symbols/SymbolManager.hpp"
#include "language/BackendRegistry.hpp"

struct LanguageContext {

  core::table::DescriptorTable descriptor_table;
  core::table::PrecedenceTable precedence_table;
  core::ModuleManager module_manager;
  SymbolManager symbol_manager;
  core::ParserScope root_scope;
  core::memory::Arena type_arena;
  BackendRegistry backends;

  LanguageContext() : root_scope(nullptr) {}
};
