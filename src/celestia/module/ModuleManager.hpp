#pragma once

#include "celestia/semantic/id/ids.hpp"
#include "celestia/module/Module.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class ModuleManager {
public:
  ModuleManager() {
    builtin_ = register_module("builtin");
    prelude_ = register_module("prelude", builtin_);
  }

  celestia::semantic::ModuleId find(std::string_view name) const {
    auto it = modules_.find(std::string(name));

    if (it == modules_.end()) return celestia::semantic::ModuleId::invalid();

    return it->second;
  }

  Module *get(celestia::semantic::ModuleId id) {
    if (!id.is_valid()) return nullptr;

    auto index = static_cast<std::size_t>(id.index());

    if (index >= storage_.size()) return nullptr;

    return storage_[index].get();
  }

  const Module *get(celestia::semantic::ModuleId id) const {
    if (!id.is_valid()) return nullptr;

    auto index = static_cast<std::size_t>(id.index());

    if (index >= storage_.size()) return nullptr;

    return storage_[index].get();
  }

  celestia::semantic::ModuleId builtin() const { return builtin_; }

  celestia::semantic::ModuleId prelude() const { return prelude_; }

  celestia::semantic::ModuleId register_module(std::string_view name) { return register_module(name, builtin_); }

private:
  celestia::semantic::ModuleId register_module(std::string_view name, celestia::semantic::ModuleId parent) {
    auto it = modules_.find(std::string(name));

    if (it != modules_.end()) return it->second;

    celestia::semantic::ModuleId id(static_cast<uint32_t>(storage_.size()));

    Module *parent_module = get(parent);

    auto module = std::make_unique<Module>(std::string(name), parent_module);

    storage_.push_back(std::move(module));
    modules_.emplace(std::string(name), id);

    return id;
  }

private:
  std::unordered_map<std::string, celestia::semantic::ModuleId> modules_;

  std::vector<std::unique_ptr<Module>> storage_;

  celestia::semantic::ModuleId builtin_ = celestia::semantic::ModuleId::invalid();
  celestia::semantic::ModuleId prelude_ = celestia::semantic::ModuleId::invalid();
};