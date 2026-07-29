#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

class Module;

class NativeModuleRegistry {

public:
  using Factory = std::function<std::shared_ptr<Module>()>;

  void register_module(std::string name, Factory factory) { modules_[std::move(name)] = std::move(factory); }

  std::shared_ptr<Module> create(std::string_view name) {

    auto it = modules_.find(std::string(name));

    if (it == modules_.end()) return nullptr;

    return it->second();
  }

private:
  std::unordered_map<std::string, Factory> modules_;
};