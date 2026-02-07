#pragma once

#include "core/memory/type.hpp"
#include "core/module/scope.hpp"
#include "frontend/symbols/SymbolId.hpp"
#include "runtime/value/ObjectValue.hpp"
#include "runtime/value/value.hpp"
#include <memory>
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
  core::ParserScope *parser_scope;
  ModuleType *type;

  std::shared_ptr<Value> module_object;

  void ensure_initialized() {
    if (initialized) return;
    if (on_module_init) on_module_init(*this);
    initialized = true;
  }

  ModuleId parent = SIZE_MAX;
  std::unordered_map<std::string, ModuleId> children;

  explicit Module(std::string n, ModuleId p = SIZE_MAX) : name(std::move(n)), parent(p) { module_object = std::make_shared<Value>(Value::Object()); }

  void add_child(const std::string &child_name, ModuleId child_id) { children[child_name] = child_id; }

  std::string full_name(const std::vector<Module> &all_modules) const {
    if (parent == SIZE_MAX) return name;
    return all_modules[parent].full_name(all_modules) + "." + name;
  }

  template <typename Fn> void add_native_function(const std::string &name, Fn &&fn) {

    SymbolId sym_id = parser_scope->resolve_symbol(name);

    if (!sym_id.is_valid()) { throw std::runtime_error("Symbol '" + name + "' not found in module parser_scope"); }

    auto val = std::make_shared<Value>(Value::Native(std::forward<Fn>(fn)));

    module_object->get_object_ref().set(name, val);
  }
};