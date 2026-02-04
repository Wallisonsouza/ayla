#pragma once

#include "core/memory/SymbolId.hpp"
#include <memory>
#include <unordered_map>

struct Value;

struct ObjectValue {
  using ObjectFields = std::unordered_map<SymbolId, std::shared_ptr<Value>>;

  ObjectFields fields;

  void set(SymbolId id, std::shared_ptr<Value> value);

  std::shared_ptr<Value> get(SymbolId id) const;
  std::shared_ptr<Value> get_or_throw(SymbolId id) const;

  bool has(SymbolId id) const;
  void remove(SymbolId id);

  size_t size() const;
};
