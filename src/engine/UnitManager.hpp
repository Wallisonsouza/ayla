#pragma once

#include "engine/CompilationUnit.hpp"

class UnitManager {

public:
  CompilationUnit *create(core::source::Source &source) {
    units.push_back(std::make_unique<CompilationUnit>(source));

    return units.back().get();
  }

  std::vector<std::unique_ptr<CompilationUnit>> &all() { return units; }

  const std::vector<std::unique_ptr<CompilationUnit>> &all() const { return units; }

private:
  std::vector<std::unique_ptr<CompilationUnit>> units;
};