#pragma once
#include <cstdint>

enum class RecoverBoundary : uint32_t { None = 0, Function = 1 << 0, Statement = 1 << 1, Variable = 1 << 2, Header = 1 << 3, If = 1 << 4 };

inline RecoverBoundary operator|(RecoverBoundary a, RecoverBoundary b) { return static_cast<RecoverBoundary>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b)); }

inline RecoverBoundary &operator|=(RecoverBoundary &a, RecoverBoundary b) {
  a = a | b;
  return a;
}