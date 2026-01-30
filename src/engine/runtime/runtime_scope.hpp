// #pragma once
// #include "core/memory/Arena.hpp"
// #include "core/memory/symbol.hpp"
// #include "core/memory/value.hpp"
// #include <unordered_map>

// struct RuntimeScope {

//   std::unordered_map<SymbolId, Value *> values;
//   RuntimeScope *parent;
//   core::memory::Arena *arena;

//   RuntimeScope(RuntimeScope *parent = nullptr) : parent(parent), arena(arena) {}

//   void set(SymbolId id, Value val) {
//     Value *stored = arena->alloc<Value>(std::move(val));
//     values[id] = stored;
//   }

//   Value get_value(SymbolId id) const {

//     if (auto it = values.find(id); it != values.end()) return *it->second;

//     if (parent) return parent->get_value(id);

//     return Value::Null();
//   }

//   Value *get_ref(SymbolId id) {

//     if (auto it = values.find(id); it != values.end()) return it->second;

//     if (parent) return parent->get_ref(id);

//     return nullptr;
//   }
// };

#pragma once
#include "core/memory/symbol.hpp"
#include "core/memory/value.hpp"
#include <unordered_map>

struct RuntimeScope {
  std::unordered_map<SymbolId, Value> values;
  RuntimeScope *parent;

  RuntimeScope(RuntimeScope *parent = nullptr) : parent(parent) {}

  void set(SymbolId id, Value val) { values[id] = val; }

  Value get(SymbolId id) {
    if (values.contains(id)) return values[id];
    if (parent) return parent->get(id);
    return Value::Null();
  }
};
