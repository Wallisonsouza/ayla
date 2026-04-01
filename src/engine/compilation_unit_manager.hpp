#pragma once

#include "ayla-compilation/unit.hpp"
#include "core/source/Source.hpp"

class CompilationUnitManager {

public:
  std::vector<std::unique_ptr<ayla::compilation::Unit>> units;

  ayla::compilation::Unit &create(ayla::compilation::Context &ctx, core::source::Source &src) {
    auto unit = std::make_unique<ayla::compilation::Unit>(ctx, src);
    auto &ref = *unit;

    units.push_back(std::move(unit));
    return ref;
  }
};