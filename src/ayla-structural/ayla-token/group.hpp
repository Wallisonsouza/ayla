#pragma once
#include <cstdint>
namespace ayla::structural::token {
enum class TokenGroup : uint8_t { Keyword, Operator, Punctuation, Literal, Whitespace, Error, NAME };
}