// #pragma once
// #include "core/memory/Arena.hpp"
// #include "engine/CompilationUnit.hpp"

// class CompilationUnitManager {
//   core::memory::Arena arena;

// public:
//   CompilationUnit *create_compilation_unit(LanguageContext &ctx, core::source::Source &src) { return arena.alloc<CompilationUnit>(ctx, src); }
// };

#include "engine/CompilationUnit.hpp"
#include <memory>
#include <vector>

class CompilationUnitManager {

public:
  std::vector<std::unique_ptr<CompilationUnit>> units;
  CompilationUnit &create(LanguageContext &ctx, core::source::Source &src) {
    auto unit = std::make_unique<CompilationUnit>(ctx, src);
    auto &ref = *unit;

    units.push_back(std::move(unit));
    return ref;
  }
};
