#pragma once

#include "module/Module.hpp"

#include <memory>
#include <string>
#include <unordered_map>

class ModuleManager {

public:
  Module *find(const std::string &name) {
    auto it = modules_.find(name);

    if (it == modules_.end()) return nullptr;

    return it->second.get();
  }

  Module *register_module(const std::string &name) {
    auto it = modules_.find(name);

    // já existe
    if (it != modules_.end()) return it->second.get();

    auto module = std::make_unique<Module>(name);

    auto *ptr = module.get();

    modules_.emplace(name, std::move(module));

    return ptr;
  }

private:
  std::unordered_map<std::string, std::unique_ptr<Module>> modules_;
};