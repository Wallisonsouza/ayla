// #pragma once

// #include <cstdint>
// #include <functional>
// #include <limits>

// struct SymbolId {
//   using ValueType = uint32_t;

//   static constexpr ValueType INVALID = std::numeric_limits<ValueType>::max();

// private:
//   ValueType value = INVALID;

// public:
//   constexpr SymbolId() = default;

//   explicit constexpr SymbolId(ValueType v) : value(v) {}

//   static constexpr SymbolId invalid() { return SymbolId(INVALID); }

//   constexpr bool is_valid() const { return value != INVALID; }

//   constexpr ValueType index() const { return value; }

//   constexpr bool operator==(const SymbolId &other) const noexcept { return value == other.value; }

//   constexpr bool operator!=(const SymbolId &other) const noexcept { return value != other.value; }
// };
// namespace std {
// template <> struct hash<SymbolId> {
//   size_t operator()(const SymbolId &id) const noexcept { return hash<uint32_t>{}(id.index()); }
// };
// } // namespace std