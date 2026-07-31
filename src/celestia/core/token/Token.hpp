#pragma once

#include "celestia/core/token/Location.hpp"
#include "celestia/core/token/TokenDescriptor.hpp"

struct Token {
  const celestia::TokenDescriptor *desc = nullptr;
  SourceSlice slice;

  constexpr Token() = default;

  constexpr Token(const celestia::TokenDescriptor *desc, SourceSlice slice) : desc(desc), slice(slice) {}
};
