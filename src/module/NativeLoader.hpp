#pragma once

#include "IModuleLoader.hpp"
#include "NativeModuleRegistry.hpp"

class NativeModuleLoader : public IModuleLoader {

public:
  explicit NativeModuleLoader(NativeModuleRegistry &registry) : registry_(registry) {}

  bool supports(ModuleSourceType type) const override { return type == ModuleSourceType::Native; }

  std::shared_ptr<Module> load(const ModuleSource &source) override { return registry_.create(source.name); }

private:
  NativeModuleRegistry &registry_;
};