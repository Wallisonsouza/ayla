#pragma once

#include "core/memory/Arena.hpp"
#include "core/module/module_manager.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"
#include "semantic/scope/scope.hpp"
#include "semantic/symbols/SymbolManager.hpp"
#include "semantic/types/type.hpp"
#include <memory>
#include <string>

struct LanguageContext {

  core::table::DescriptorTable descriptor_table;
  core::table::PrecedenceTable precedence_table;
  std::unordered_map<std::string, std::shared_ptr<Type>> type_table;
  core::ModuleManager module_manager;
  SymbolManager symbol_manager;
  core::ParserScope root_scope;
  core::memory::Arena type_arena;

  explicit LanguageContext() : root_scope(nullptr) {}
};
