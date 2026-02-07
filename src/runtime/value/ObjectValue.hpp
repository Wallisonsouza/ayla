#pragma once
#include <memory>
#include <unordered_map>

struct Value;

struct ObjectValue {
  using ObjectFields = std::unordered_map<std::string, std::shared_ptr<Value>>;

  ObjectFields fields;

  void set(const std::string &name, std::shared_ptr<Value> value) { fields[name] = std::move(value); }

  std::shared_ptr<Value> get(const std::string &name) const {
    auto it = fields.find(name);
    return it != fields.end() ? it->second : nullptr;
  }

  std::shared_ptr<Value> get_or_throw(const std::string &name) const {
    auto v = get(name);
    if (!v) throw std::runtime_error("Field not found: " + name);
    return v;
  }

  bool has(const std::string &name) const { return fields.find(name) != fields.end(); }

  void remove(const std::string &name) { fields.erase(name); }

  size_t size() const { return fields.size(); }
};
