#include "ObjectValue.hpp"
#include <stdexcept>

void ObjectValue::set(SymbolId id, std::shared_ptr<Value> value) { fields[id] = std::move(value); }

std::shared_ptr<Value> ObjectValue::get(SymbolId id) const {
  auto it = fields.find(id);
  if (it != fields.end()) return it->second;

  return nullptr;
}

std::shared_ptr<Value> ObjectValue::get_or_throw(SymbolId id) const {
  auto it = fields.find(id);
  if (it == fields.end()) throw std::runtime_error("Object field not found");

  return it->second;
}

bool ObjectValue::has(SymbolId id) const { return fields.find(id) != fields.end(); }

void ObjectValue::remove(SymbolId id) { fields.erase(id); }

size_t ObjectValue::size() const { return fields.size(); }
