#pragma once

#include "ayla/source/source_location.hpp"
#include "core/token/TokenDescriptor.hpp"

struct Token {
  const TokenDescriptor *descriptor = nullptr;
  SourceSlice slice;

  constexpr Token() = default;

  constexpr Token(const TokenDescriptor *desc, SourceSlice slice) : descriptor(desc), slice(slice) {}
};
