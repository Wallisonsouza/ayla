#pragma once

#include "core/memory/symbol.hpp"
#include <string>
#include <unordered_map>

namespace core {

struct SymbolEntry {
  SymbolId id;
};

struct ParserScope {

  ParserScope *parent = nullptr;
  std::unordered_map<std::string, SymbolId> table;

  ParserScope(ParserScope *p = nullptr) : parent(p) {}

  void declare(const std::string &name, SymbolId id) { table[name] = id; }

  SymbolId resolve_symbol(const std::string &name) const {
    auto it = table.find(name);
    if (it != table.end()) return it->second;

    if (parent) return parent->resolve_symbol(name);

    return INVALID_SYMBOL_ID;
  }

  bool has_symbol_local(const std::string &name) const { return table.count(name); }
};

} // namespace core
