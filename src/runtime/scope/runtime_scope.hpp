#pragma once

#include "core/memory/SymbolId.hpp"
#include "runtime/value/value.hpp"
#include <stdexcept>
#include <unordered_map>
#include <vector>

struct RuntimeScope {

  RuntimeScope *parent;

  std::unordered_map<SymbolId, std::shared_ptr<Value>> values;

  std::vector<RuntimeScope *> imports;

  RuntimeScope(RuntimeScope *parent = nullptr) : parent(parent) {}

  void set(SymbolId id, std::shared_ptr<Value> val) { values[id] = std::move(val); }

  void import(RuntimeScope *scope) { imports.push_back(scope); }

  std::shared_ptr<Value> get(SymbolId id) {

    if (auto it = values.find(id); it != values.end()) return it->second;

    for (auto imp : imports) {
      try {
        return imp->get(id);
      } catch (const std::runtime_error &) {}
    }

    if (parent) return parent->get(id);

    throw std::runtime_error("Undefined variable");
  }
};
