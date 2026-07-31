#pragma once

#include "celestia/semantic/types/type.hpp"

#include <string>
#include <unordered_map>

namespace core::table {

class TypeTable {

public:
  void add(std::string name, celestia::semantic::Type *type) { types.emplace(std::move(name), type); }

  celestia::semantic::Type *find(const std::string &name) const {
    auto it = types.find(name);

    if (it == types.end()) return nullptr;

    return it->second;
  }

  bool contains(const std::string &name) const { return types.contains(name); }

private:
  std::unordered_map<std::string, celestia::semantic::Type *> types;
};

} // namespace core::table