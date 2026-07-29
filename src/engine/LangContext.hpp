#pragma once

#include "core/memory/Arena.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"
#include "module/ModuleManager.hpp"
#include "semantic/scope/Scope.hpp"
#include "semantic/symbols/SymbolManager.hpp"
#include "semantic/types/type.hpp"
#include <memory>
#include <string>

struct LanguageContext {

  core::table::DescriptorTable descriptors;
  core::table::OperatorTable operators;
  std::unordered_map<std::string, std::shared_ptr<Type>> type_table;
  SymbolManager symbols;
  core::Scope root_scope;
  core::memory::Arena type_arena;
  ModuleManager modules;

  explicit LanguageContext() : root_scope(nullptr) {}
};
