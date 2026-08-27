#pragma once

#include "celestia/module/Module.hpp"

#include <memory>
#include <string>
#include <unordered_map>

class ModuleManager {

public:
  ModuleManager() {

    builtin_ = register_module("builtin", nullptr);

    prelude_ = register_module("prelude", builtin_);
  }

  Module *find(const std::string &name) {

    auto it = modules_.find(name);

    if (it == modules_.end()) return nullptr;

    return it->second.get();
  }

  Module *builtin() const { return builtin_; }

  Module *prelude() const { return prelude_; }

  Module *register_module(const std::string &name) { return register_module(name, builtin_); }

private:
  Module *register_module(const std::string &name, Module *parent) {

    auto it = modules_.find(name);

    // Já existe.
    if (it != modules_.end()) return it->second.get();

    auto module = std::make_unique<Module>(name, parent);

    auto *ptr = module.get();

    modules_.emplace(name, std::move(module));

    return ptr;
  }

private:
  std::unordered_map<std::string, std::unique_ptr<Module>> modules_;

  Module *builtin_ = nullptr;
  Module *prelude_ = nullptr;
};