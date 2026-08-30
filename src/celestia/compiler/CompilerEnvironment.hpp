#pragma once

#include "celestia/compiler/TypeManager.hpp"
#include "celestia/language/LanguageDefinition.hpp"
#include "celestia/module/ModuleManager.hpp"
#include "celestia/semantic/symbol/SymbolManager.hpp"

struct BuiltinTypes {
  celestia::semantic::TypeId int_type = celestia::semantic::TypeId::invalid();
  celestia::semantic::TypeId uint_type = celestia::semantic::TypeId::invalid();

  celestia::semantic::TypeId int8_type = celestia::semantic::TypeId::invalid();
  celestia::semantic::TypeId int16_type = celestia::semantic::TypeId::invalid();
  celestia::semantic::TypeId int32_type = celestia::semantic::TypeId::invalid();
  celestia::semantic::TypeId int64_type = celestia::semantic::TypeId::invalid();

  celestia::semantic::TypeId uint8_type = celestia::semantic::TypeId::invalid();
  celestia::semantic::TypeId uint16_type = celestia::semantic::TypeId::invalid();
  celestia::semantic::TypeId uint32_type = celestia::semantic::TypeId::invalid();
  celestia::semantic::TypeId uint64_type = celestia::semantic::TypeId::invalid();

  celestia::semantic::TypeId f32_type = celestia::semantic::TypeId::invalid();
  celestia::semantic::TypeId f64_type = celestia::semantic::TypeId::invalid();

  celestia::semantic::TypeId bool_type = celestia::semantic::TypeId::invalid();
  celestia::semantic::TypeId char_type = celestia::semantic::TypeId::invalid();
  celestia::semantic::TypeId string_type = celestia::semantic::TypeId::invalid();
  celestia::semantic::TypeId void_type = celestia::semantic::TypeId::invalid();
};

struct BuiltinIntrinsics {
  celestia::semantic::SymbolId array = celestia::semantic::SymbolId ::invalid();
  celestia::semantic::SymbolId  map = celestia::semantic::SymbolId ::invalid();
  celestia::semantic::SymbolId  set = celestia::semantic::SymbolId ::invalid();
  celestia::semantic::SymbolId  ref = celestia::semantic::SymbolId ::invalid();
};

struct CompilerEnvironment {

  celestia::LanguageDefinition language;

  SymbolManager symbols;

  ModuleManager modules;

  TypeManager types;

  BuiltinTypes builtins;

  BuiltinIntrinsics intrinsics;

  CompilerEnvironment() = default;
};