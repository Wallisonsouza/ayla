#pragma once

#include <cstdint>
#include <functional>
#include <limits>

template <typename Tag> class Id {
public:
  using ValueType = uint32_t;

  static constexpr ValueType INVALID = std::numeric_limits<ValueType>::max();

private:
  ValueType value = INVALID;

public:
  constexpr Id() = default;

  explicit constexpr Id(ValueType v) : value(v) {}

  static constexpr Id invalid() { return Id(INVALID); }

  constexpr bool is_valid() const { return value != INVALID; }

  constexpr ValueType index() const { return value; }

  constexpr bool operator==(const Id &other) const noexcept { return value == other.value; }

  constexpr bool operator!=(const Id &other) const noexcept { return value != other.value; }
};

namespace std {

template <typename Tag> struct hash<Id<Tag>> {
  size_t operator()(const Id<Tag> &id) const noexcept { return hash<uint32_t>{}(id.index()); }
};

} // namespace std