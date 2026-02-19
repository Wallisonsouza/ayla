#pragma once

#include "semantic/symbols/SymbolId.hpp"
#include <optional>
#include <string>
#include <unordered_map>

enum class ResolvedKind { Local, Upvalue, Global };

struct ResolvedRef {
  ResolvedKind kind;
  uint32_t slot;
};

namespace core {

struct ParserScope {
  ParserScope *parent = nullptr;

  std::unordered_map<std::string, SymbolId> table;
  std::unordered_map<SymbolId, uint32_t> slots;
  bool is_function_scope = false;
  uint32_t next_slot = 0;

  explicit ParserScope(ParserScope *p = nullptr) : parent(p) {}

  uint32_t declare(const std::string &name, SymbolId id) {
    table.insert_or_assign(name, id);

    uint32_t slot = next_slot++;
    slots[id] = slot;

    return slot;
  }

  SymbolId resolve_symbol(const std::string &name) const {
    const ParserScope *scope = this;

    while (scope) {
      auto it = scope->table.find(name);
      if (it != scope->table.end()) return it->second;

      scope = scope->parent;
    }

    return SymbolId();
  }

  std::optional<uint32_t> resolve_slot(SymbolId id) const {
    const ParserScope *scope = this;

    while (scope) {
      auto it = scope->slots.find(id);
      if (it != scope->slots.end()) return it->second;

      scope = scope->parent;
    }

    return std::nullopt;
  }

  std::optional<ResolvedRef> resolve_ref(SymbolId id) const {
    const ParserScope *scope = this;

    bool crossed_function = false;

    while (scope) {
      auto it = scope->slots.find(id);

      if (it != scope->slots.end()) {
        if (!crossed_function) return ResolvedRef{ResolvedKind::Local, it->second};

        return ResolvedRef{ResolvedKind::Upvalue, it->second};
      }

      if (scope->is_function_scope) crossed_function = true;

      scope = scope->parent;
    }

    return ResolvedRef{ResolvedKind::Global, 0};
  }

  uint32_t allocate_temporary() { return next_slot++; }
  bool has_symbol_local(const std::string &name) const { return table.find(name) != table.end(); }
};

} // namespace core
