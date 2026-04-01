#pragma once

#include "ayla-source/source_location.hpp"
#include "ayla-structural/ayla-token/descriptor.hpp"

namespace ayla::structural::token {
struct Token {

  ayla::source::SourceSlice slice;
  const TokenDescriptor *descriptor = nullptr;

  constexpr Token() = default;

  constexpr Token(const TokenDescriptor *desc, ayla::source::SourceSlice slice) : descriptor(desc), slice(slice) {}
};
} // namespace ayla::structural::token