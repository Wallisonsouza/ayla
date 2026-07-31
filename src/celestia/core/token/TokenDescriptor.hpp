#pragma once

#include "celestia/core/token/TokenGroup.hpp"
#include "celestia/core/token/TokenKind.hpp"
#include "celestia/semantic/types/type.hpp"

#include <string>
#include <vector>

namespace celestia {

struct TokenDescriptor {

  TokenKind kind;
  TokenGroup group;

  std::string name;

  std::vector<std::string> aliases;

  semantic::Type *literal_type = nullptr;

  TokenDescriptor(TokenKind kind, TokenGroup group, const std::string &lexeme, semantic::Type *type = nullptr) : kind(kind), group(group), name(lexeme), literal_type(type) {}
};

} // namespace celestia