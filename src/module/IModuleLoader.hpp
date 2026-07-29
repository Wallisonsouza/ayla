#pragma once

#include "Module.hpp"
#include "ModuleSource.hpp"

#include <memory>

class IModuleLoader {
public:
  virtual ~IModuleLoader() = default;

  virtual bool supports(ModuleSourceType type) const = 0;

  virtual std::shared_ptr<Module> load(const ModuleSource &source) = 0;
};