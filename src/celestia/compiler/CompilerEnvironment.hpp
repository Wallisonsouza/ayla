#pragma once


#include "celestia/language/LanguageDefinition.hpp"
#include "celestia/module/ModuleManager.hpp"

#include "celestia/semantic/symbols/SymbolManager.hpp"

#include "celestia/core/memory/Arena.hpp"


struct CompilerEnvironment {

    celestia::LanguageDefinition language;

    SymbolManager symbols;

    ModuleManager modules;

    core::memory::Arena type_arena;
};