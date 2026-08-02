#include "TokenDumper.hpp"
#include "celestia/core/source/SourceBuffer.hpp"
#include "celestia/core/token/TokenKind.hpp"
#include <iostream>
#include <sstream>

namespace celestia::debug {

constexpr const char *TokenDumper::token_group_to_str(TokenGroup grp) {
  using G = TokenGroup;

  switch (grp) {
  case G::Name: return "Name";
  case G::Keyword: return "Keyword";
  case G::Operator: return "Operator";
  case G::Punctuation: return "Punctuation";
  case G::Error: return "Error";
  case G::Literal: return "Literal";
  }

  return "<UnknownGroup>";
}

constexpr const char *TokenDumper::token_kind_to_str(TokenKind kin) {

  switch (kin) {
  case TokenKind::MODULE_KEYWORD: return "MODULE_KEYWORD";
  case TokenKind::STATIC: return "STATIC";
  case TokenKind::MUT: return "MUT";
  case TokenKind::PUBLIC: return "PUBLIC";
  case TokenKind::PRIVATE: return "PRIVATE";
  case TokenKind::INVALID: return "INVALID";
  case TokenKind::COMMENT: return "COMMENT";
  case TokenKind::VALUE_KEYWORD: return "VALUE_KEYWORD";
  case TokenKind::CONST: return "CONST_KEYWORD";
  case TokenKind::FUNCTION_KEYWORD: return "FUNCTION_KEYWORD";

  case TokenKind::OPEN_BRACKET: return "OPEN_BRACKET";
  case TokenKind::CLOSE_BRACKET: return "CLOSE_BRACKET";

  case TokenKind::NEW_LINE: return "NEW_LINE";
  case TokenKind::IMPORT_KEYWORD: return "IMPORT_KEYWORD";
  case TokenKind::DOT: return "DOT";

  case TokenKind::IF_KEYWORD: return "IF_KEYWORD";
  case TokenKind::ELSE_KEYWORD: return "ELSE_KEYWORD";
  case TokenKind::RETURN_KEYWORD: return "RETURN_KEYWORD";

  case TokenKind::EQUAL: return "EQUAL";
  case TokenKind::ASSIGN: return "ASSIGN";

  case TokenKind::Ternary: return "Ternary";

  case TokenKind::PLUS: return "PLUS";
  case TokenKind::MINUS: return "MINUS";
  case TokenKind::STAR: return "STAR";
  case TokenKind::SLASH: return "SLASH";

  case TokenKind::COLON: return "COLON";
  case TokenKind::COMMA: return "Comma";
  case TokenKind::SEMI_COLON: return "Semicolon";

  case TokenKind::OPEN_PAREN: return "OPEN_PAREN";
  case TokenKind::CLOSE_PAREN: return "CLOSE_PAREN";

  case TokenKind::OPEN_BRACE: return "OPEN_BRACE";
  case TokenKind::CLOSE_BRACE: return "CLOSE_BRACE";

  case TokenKind::IDENTIFIER: return "IDENTIFIER";

  case TokenKind::NUMBER_LITERAL: return "NUMBER_LITERAL";
  case TokenKind::STRING_LITERAL: return "STRING_LITERAL";

  case TokenKind::Space: return "Space";
  case TokenKind::EndOfFile: return "EndOfFile";
  }

  return "<UnknownKind>";
}

std::string TokenDumper::sanitize_text(std::string text, size_t max) {
  for (char &c : text) {
    if (c == '\n')
      c = '~';
    else if (c == '\t')
      c = '>';
  }

  if (text.size() > max) text = text.substr(0, max) + "...";

  return text;
}

std::string TokenDumper::dump_token(const Token &token, const core::source::SourceBuffer &source) {
  const char *kind = "<no-descriptor>";
  const char *group = "<no-descriptor>";

  if (token.desc) {
    kind = token_kind_to_str(token.desc->kind);
    group = token_group_to_str(token.desc->group);
  }

  std::string_view view = source.get_view(token.slice.get_span());

  std::ostringstream oss;

  oss << "Token {\n"
      << "  kind  : " << kind << "\n"
      << "  group : " << group << "\n"
      << "  text  : \"" << sanitize_text(std::string(view)) << "\"\n"
      << "  range : " << token.slice.begin.line << ":" << token.slice.begin.column << " -> " << token.slice.end.line << ":" << token.slice.end.column << "\n"
      << "  offset: " << token.slice.begin.offset << " -> " << token.slice.end.offset << "\n"
      << "}";

  return oss.str();
}

std::string TokenDumper::dump(const core::token::TokenStream &tokens, const core::source::SourceBuffer &source) {
  std::ostringstream oss;

  for (auto &token : tokens.get_tokens()) { oss << dump_token(*token, source) << "\n\n"; }

  return oss.str();
}

} // namespace celestia::debug