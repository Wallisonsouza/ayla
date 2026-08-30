#pragma once

#include "celestia/semantic/id/ids.hpp"
#include "celestia/semantic/symbol/SymbolTable.hpp"
#include <string_view>

namespace core {

enum class ScopeKind {
  Module,
  Function,
  Struct,
  Type,
  Block,
  Capability,
  Impl,
};

struct Scope {

  Scope *parent = nullptr;

  SymbolTable symbols;
  ScopeKind kind;

  explicit Scope(ScopeKind kind, Scope *p = nullptr) : parent(p), kind(kind) {}

  celestia::semantic::SymbolId symbol(std::string_view name) const {
    const Scope *scope = this;

    while (scope) {
      celestia::semantic::SymbolId id = scope->symbols.find(name);

      if (id.is_valid()) return id;

      scope = scope->parent;
    }

    return celestia::semantic::SymbolId::invalid();
  }

  bool has_symbol_local(std::string_view name) const { return symbols.contains(name); }
};

} // namespace core