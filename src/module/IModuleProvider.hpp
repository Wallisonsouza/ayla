#pragma once

#include "ModuleSource.hpp"

#include <optional>
#include <string_view>

class IModuleProvider {
public:
  virtual ~IModuleProvider() = default;

  virtual std::optional<ModuleSource> resolve(std::string_view name) = 0;
};