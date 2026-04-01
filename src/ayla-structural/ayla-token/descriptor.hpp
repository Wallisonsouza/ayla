#pragma once

#include "ayla-structural/ayla-token/group.hpp"
#include "ayla-structural/ayla-token/kind.hpp"

#include <string>
#include <vector>

namespace ayla::structural::token {
struct TokenDescriptor {

  const TokenKind kind;
  const TokenGroup group;
  const std::string name;
  std::vector<std::string> aliases;

  TokenDescriptor(TokenKind kind, TokenGroup group, const std::string &lexeme) : kind(kind), group(group), name(lexeme) {}
};
} // namespace ayla::structural::token