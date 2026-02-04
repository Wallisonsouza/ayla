#pragma once
#include "core/memory/SymbolId.hpp"
#include <string>
#include <unordered_map>

namespace core {

struct ParserScope {
  ParserScope *parent = nullptr;
  std::unordered_map<std::string, SymbolId> table;

  explicit ParserScope(ParserScope *p = nullptr) : parent(p) {}

  void declare(const std::string &name, SymbolId id) { table.insert_or_assign(name, id); }

  SymbolId resolve_symbol(const std::string &name) const {
    const ParserScope *scope = this;

    while (scope) {
      auto it = scope->table.find(name);
      if (it != scope->table.end()) return it->second;

      scope = scope->parent;
    }

    return SymbolId();
  }

  bool has_symbol_local(const std::string &name) const { return table.find(name) != table.end(); }
};

} // namespace core
