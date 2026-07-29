#pragma once

#include "core/token/TokenKind.hpp"

#include <optional>

namespace diagnostic {

enum class ExpectedKind {
  Token,

  Identifier,

  Expression,

  Pattern,

  Type,

  Declaration
};

struct Expected {
  ExpectedKind kind;

  std::optional<TokenKind> token;
};

struct Found {
  TokenKind token;
};

} // namespace diagnostic