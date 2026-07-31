#pragma once

#include "celestia/core/source/SourceBuffer.hpp"
#include "celestia/core/token/Token.hpp"
#include "celestia/core/token/TokenGroup.hpp"
#include "celestia/core/token/TokenKind.hpp"
#include "celestia/core/token/token_stream.hpp"

#include <string>

namespace debug::lexer {

class TokenDumper {
public:

  std::string dump_token(const Token &token, const core::source::SourceBuffer &source) ;

  std::string dump(const core::token::TokenStream &tokens, const core::source::SourceBuffer &source);

private:
  static constexpr const char *token_group_to_str(TokenGroup group);

  static constexpr const char *token_kind_to_str(TokenKind kind);

  static std::string sanitize_text(std::string text, size_t max = 40);
};

} // namespace debug::lexer