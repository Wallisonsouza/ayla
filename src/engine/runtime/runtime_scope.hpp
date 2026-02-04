#pragma once
#include "core/memory/symbol.hpp"
#include "core/memory/value.hpp"
#include <stdexcept>
#include <unordered_map>

struct RuntimeScope {

  RuntimeScope *parent;

  std::unordered_map<SymbolId, std::shared_ptr<Value>> values;

  RuntimeScope(RuntimeScope *parent = nullptr) : parent(parent) {}

  void set(SymbolId id, std::shared_ptr<Value> val) { values[id] = std::move(val); }

  std::shared_ptr<Value> get(SymbolId id) {
    if (auto it = values.find(id); it != values.end()) return it->second;
    if (parent) return parent->get(id);
    throw std::runtime_error("Undefined variable");
  }
};
