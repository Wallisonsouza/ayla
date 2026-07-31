#pragma once
#include <cstdint>

enum class TokenGroup : uint8_t {
  Keyword,
  Operator,
  Punctuation,
  Literal,
  Whitespace,
  Error,
  Name
};