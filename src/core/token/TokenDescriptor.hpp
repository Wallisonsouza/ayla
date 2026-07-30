#pragma once
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include <string>
#include <vector>

struct TokenDescriptor {

   TokenKind kind;
   TokenGroup group;
   std::string name;
  std::vector<std::string> aliases;

  TokenDescriptor(TokenKind kind, TokenGroup group, const std::string &lexeme)
      : kind(kind), group(group), name(lexeme) {}
};
