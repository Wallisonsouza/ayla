#pragma once

#include "celestia/compiler/IntrinsicRegistry.hpp"
#include "celestia/compiler/TypeManager.hpp"
#include "celestia/language/LanguageDefinition.hpp"
#include "celestia/module/ModuleManager.hpp"
#include "celestia/semantic/symbol/SymbolManager.hpp"

struct CompilerEnvironment {

  celestia::LanguageDefinition language;

  SymbolManager symbols;

  ModuleManager modules;

  TypeManager types;

  celestia::IntrinsicRegistry intrinsics;

  CompilerEnvironment() = default;
};