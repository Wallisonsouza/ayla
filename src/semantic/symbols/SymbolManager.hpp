#pragma once
#include "SymbolId.hpp"
#include "semantic/symbols/Symbol.hpp"

#include <deque>
#include <stdexcept>

struct SymbolManager {
  std::deque<Symbol> symbols;

private:
  uint32_t next_id = 0;

public:
  SymbolId create_symbol(const std::string &name, SymbolKind kind, Visibility visibility = Visibility::Private, bool is_builtin = false, ayla::ast::AstNode *decl = nullptr) {

    if (next_id == SymbolId::INVALID) { throw std::runtime_error("SymbolId overflow"); }

    SymbolId id(next_id++);
    symbols.emplace_back(name, kind, visibility, is_builtin, decl);

    return id;
  }

  Symbol *get(SymbolId id) {
    if (!id.is_valid()) return nullptr;

    uint32_t i = id.value;

    if (i >= symbols.size()) return nullptr;

    return &symbols[i];
  }

  const Symbol *get(SymbolId id) const {
    if (!id.is_valid()) return nullptr;

    uint32_t i = id.value;

    if (i >= symbols.size()) return nullptr;

    return &symbols[i];
  }

  size_t size() const { return symbols.size(); }
};