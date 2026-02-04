#pragma once

#include "core/memory/value.hpp"
#include "engine/runtime/runtime_scope.hpp"
#include <string>
#include <unordered_map>
#include <vector>

using ModuleId = size_t;

inline constexpr ModuleId INVALID_MODULE = SIZE_MAX;

struct Module {

  using ModuleInitFn = std::function<void(Module &)>;

  ModuleInitFn on_module_init;
  bool initialized = false;
  std::string name;
  RuntimeScope runtime_scope;

  void ensure_initialized() {
    if (initialized) return;
    if (on_module_init) on_module_init(*this);
    initialized = true;
  }

  ModuleId parent = SIZE_MAX;
  std::unordered_map<std::string, ModuleId> children;

  explicit Module(std::string n, ModuleId p = SIZE_MAX) : name(std::move(n)), parent(p) {}

  void add_child(const std::string &child_name, ModuleId child_id) { children[child_name] = child_id; }

  std::string full_name(const std::vector<Module> &all_modules) const {
    if (parent == SIZE_MAX) return name;
    return all_modules[parent].full_name(all_modules) + "." + name;
  }

  template <typename Fn> void add_native_function(const std::string &name, Fn &&fn) {

    auto object = Value::ObjectValue({});

    // auto existing = parser_scope.resolve(name);

    // if (!existing) { throw std::runtime_error("Native function '" + name + "' not declared as extern"); }

    // runtime_scope.set(existing->id, std::make_shared<Value>(Value::Native(std::forward<Fn>(fn))));
  }
};