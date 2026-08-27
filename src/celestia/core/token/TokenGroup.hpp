#pragma once

#include <cstdint>
#include <string_view>

enum class TokenGroup : uint8_t {
  Keyword,
  Operator,
  Punctuation,
  Literal,
  Whitespace,
  Error,
  Name
};

constexpr std::string_view token_group_name(TokenGroup group) noexcept {
  switch (group) {
  case TokenGroup::Keyword:     return "Keyword";
  case TokenGroup::Operator:    return "Operator";
  case TokenGroup::Punctuation: return "Punctuation";
  case TokenGroup::Literal:     return "Literal";
  case TokenGroup::Whitespace:  return "Whitespace";
  case TokenGroup::Error:       return "Error";
  case TokenGroup::Name:        return "Name";
  }

  return "Unknown";
}