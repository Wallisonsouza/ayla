#pragma once

#include "core/token/Token.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"

#include <string>

namespace debug::lexer {

class TokenDumper {
public:
  std::string dump(const Token &token);

  std::string dump(const core::token::TokenStream &tokens);

private:
  static constexpr const char *token_group_to_str(TokenGroup group);

  static constexpr const char *token_kind_to_str(TokenKind kind);

  static std::string sanitize_text(std::string text, size_t max = 40);
};

} // namespace debug::lexer