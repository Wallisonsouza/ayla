#pragma once
#include "symbol.hpp"
#include <stdexcept>
#include <string>
#include <vector>

struct SymbolManager {
private:
  std::vector<Symbol> symbols;
  SymbolId next_id = SymbolId(0);

public:
  SymbolId create_symbol(const std::string &name, SymbolKind kind, Visibility visibility = Visibility::Private, bool is_builtin = false, core::ast::ASTNode *decl = nullptr) {

    SymbolId id = next_id++;

    symbols.emplace_back(name, kind, visibility, is_builtin, decl);

    return id;
  }

  Symbol *get(SymbolId id) {
    if (!id.is_valid() || static_cast<size_t>(id) >= symbols.size()) throw std::out_of_range("Invalid SymbolId");

    return &symbols[static_cast<size_t>(id)];
  }

  void reset() {
    symbols.clear();
    next_id = SymbolId(0);
  }
};
