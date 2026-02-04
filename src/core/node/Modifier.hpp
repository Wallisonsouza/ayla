#pragma once
#include <cstdint>
#include <vector>

namespace core::ast {

enum class Modifier : uint8_t { None = 0, Value = 1 << 0, Static = 1 << 1, Mut = 1 << 2, Public = 1 << 3, Private = 1 << 4, Extern = 1 << 5 };

inline Modifier operator|(Modifier a, Modifier b) { return static_cast<Modifier>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b)); }

inline Modifier &operator|=(Modifier &a, Modifier b) {
  a = a | b;
  return a;
}

inline Modifier operator&(Modifier a, Modifier b) { return static_cast<Modifier>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b)); }

struct Modifiers {
  std::vector<core::ast::Modifier> order;
  Modifier mask = Modifier::None;

  void add(Modifier m) {
    order.push_back(m);
    mask |= m;
  }

  bool has(Modifier m) const { return (static_cast<uint8_t>(mask) & static_cast<uint8_t>(m)) != 0; }
};

} // namespace core::ast
