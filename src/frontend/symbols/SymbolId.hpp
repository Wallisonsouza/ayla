#pragma once
#include <cstdint>
#include <functional>
#include <limits>

struct SymbolId {
  uint32_t value;

  static constexpr uint32_t INVALID = std::numeric_limits<uint32_t>::max();

  constexpr SymbolId() : value(INVALID) {}

  explicit constexpr SymbolId(uint32_t v) : value(v) {}

  constexpr bool is_valid() const { return value != INVALID; }

  constexpr bool operator==(SymbolId other) const { return value == other.value; }
  constexpr bool operator!=(SymbolId other) const { return value != other.value; }
  constexpr bool operator<(SymbolId other) const { return value < other.value; }
};

namespace std {
template <> struct hash<SymbolId> {
  size_t operator()(const SymbolId &id) const noexcept { return std::hash<uint32_t>{}(id.value); }
};
} // namespace std
