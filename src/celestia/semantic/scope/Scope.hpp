#pragma once

#include "celestia/semantic/symbols/SymbolId.hpp"
#include "celestia/semantic/symbols/SymbolTable.hpp"
#include <string_view>

namespace core {

enum class ScopeKind {
  Module,
  Function,
  Struct,
  Block,
  Capability,
  Impl,
};

struct Scope {

  Scope *parent = nullptr;

  SymbolTable symbols;
  ScopeKind kind;

  explicit Scope(ScopeKind kind, Scope *p = nullptr) : parent(p), kind(kind) {}

  SymbolId symbol(std::string_view name) const {
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