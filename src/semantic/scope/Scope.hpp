#pragma once

#include "semantic/symbols/SymbolId.hpp"
#include "semantic/symbols/SymbolTable.hpp"
#include <string_view>

namespace core {

struct Scope {

  Scope *parent = nullptr;

  SymbolTable symbols;

  explicit Scope(Scope *p = nullptr) : parent(p) {}

  SymbolId resolve_symbol(std::string_view name) const {
    const Scope *scope = this;

    while (scope) {
      SymbolId id = scope->symbols.find(name);

      if (id.is_valid()) return id;

      scope = scope->parent;
    }

    return SymbolId::invalid();
  }

  bool has_symbol_local(std::string_view name) const { return symbols.contains(name); }
};

} // namespace core