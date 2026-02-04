#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

enum class Visibility { Private, Public };
enum class SymbolKind { Type, Function, Variable, Field, Module };

struct Type;

namespace core::ast {
struct ASTNode;
}

struct Symbol {
  std::string name;
  SymbolKind kind;
  Visibility visibility;
  bool is_builtin;
  Type *type = nullptr;
  size_t module_id;
  core::ast::ASTNode *declaration = nullptr;

  Symbol(std::string name, SymbolKind kind, Visibility visibility = Visibility::Private, bool is_builtin = false, core::ast::ASTNode *decl = nullptr)
      : name(std::move(name)), kind(kind), visibility(visibility), is_builtin(is_builtin), declaration(decl) {}
};

inline constexpr size_t INVALID_SYMBOL = SIZE_MAX;

struct SymbolId {
  size_t value;

  constexpr SymbolId() : value(INVALID_SYMBOL) {}
  explicit constexpr SymbolId(size_t v) : value(v) {}

  constexpr bool is_valid() const { return value != INVALID_SYMBOL; }

  SymbolId &operator++() {
    ++value;
    return *this;
  }

  SymbolId operator++(int) {
    SymbolId tmp = *this;
    ++value;
    return tmp;
  }
  constexpr bool operator==(const SymbolId &other) const { return value == other.value; }
  constexpr bool operator!=(const SymbolId &other) const { return value != other.value; }
  constexpr bool operator<(const SymbolId &other) const { return value < other.value; }

  constexpr operator size_t() const { return value; }
};

namespace std {
template <> struct hash<SymbolId> {
  size_t operator()(const SymbolId &id) const noexcept { return std::hash<size_t>{}(id.value); }
};
} // namespace std

inline constexpr SymbolId INVALID_SYMBOL_ID = SymbolId(INVALID_SYMBOL);