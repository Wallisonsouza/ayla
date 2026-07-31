#pragma once

#include "module/ModuleSource.hpp"
#include <memory>
#include <module/Module.hpp>

class Module;

class IModuleLoader {

public:
  virtual ~IModuleLoader() = default;

  virtual bool supports(const ModuleSource &source) const = 0;

  virtual std::shared_ptr<Module> load(const ModuleSource &source) = 0;
};