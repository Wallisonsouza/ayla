#pragma once
#include "Symbol.hpp"
#include "celestia/semantic/symbol/Symbol.hpp"

#include <deque>
#include <stdexcept>

struct SymbolManager {
  std::deque<Symbol> symbols;

private:
  uint32_t next_id = 0;

public:
  celestia::semantic::SymbolId create_symbol(const std::string &name, SymbolKind kind, Visibility visibility = Visibility::Private, bool is_builtin = false, celestia::ast::Node *decl = nullptr) {

    if (next_id == celestia::semantic::SymbolId::INVALID) { throw std::runtime_error("celestia::semantic::SymbolId overflow"); }

    celestia::semantic::SymbolId id(next_id++);
    symbols.emplace_back(id, name, kind, visibility, is_builtin, decl);

    return id;
  }

  Symbol *get(celestia::semantic::SymbolId id) {
    if (!id.is_valid()) return nullptr;

    uint32_t i = id.index();

    if (i >= symbols.size()) return nullptr;

    return &symbols[i];
  }

  const Symbol *get(celestia::semantic::SymbolId id) const {
    if (!id.is_valid()) return nullptr;

    uint32_t i = id.index();

    if (i >= symbols.size()) return nullptr;

    return &symbols[i];
  }

  size_t size() const { return symbols.size(); }
};