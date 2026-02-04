#pragma once

#include "core/token/Token.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "debug/console/console.hpp"
#include <sstream>
#include <string>

namespace debug::engine {

constexpr const char *token_group_to_str(TokenGroup grp) {
  using G = TokenGroup;
  switch (grp) {
  case G::NAME: return "Name";
  case G::Keyword: return "Keyword";
  case G::Operator: return "Operator";
  case G::Punctuation: return "Punctuation";
  case G::Error: return "Error";
  case G::Literal: return "Literal";
  }
  return "<UnknownGroup>";
}

constexpr const char *token_kind_to_str(TokenKind kin) {
  using K = TokenKind;
  switch (kin) {

  case K::STATIC: return "STATIC";
  case K::MUT: return "MUT";
  case K::PUBLIC: return "PUBLIC";
  case K::PRIVATE: return "PRIVATE";
  case K::INVALID: return "INVALID";
  case K::COMMENT: return "COMMENT";
  case K::VALUE_KEYWORD: return "VALUE_KEYWORD";
  case K::CONST_KEYWORD: return "CONST_KEYWORD";
  case K::FUNCTION_KEYWORD: return "FUNCTION_KEYWORD";
  case K::OPEN_BRACKET: return "OPEN_BRACKET";
  case K::CLOSE_BRACKET: return "CLOSE_BRACKET";

  case K::NEW_LINE: return "Newline";
  case K::IMPORT_KEYWORD: return "IMPORT_KEYWORD";
  case K::DOT: return "DOT";
  case K::IF_KEYWORD: return "If";
  case K::ELSE_KEYWORD: return "ELSE_KEYWORD"; return "For";
  case K::RETURN_KEYWORD: return "RETURN_KEYWORD";
  case K::EQUAL: return "EQUAL";
  case K::ASSIGN: return "ASSIGN";
  case K::Ternary: return "Ternary";
  case K::PLUS: return "PLUS";
  case K::MINUS: return "MINUS";
  case K::STAR: return "STAR";
  case K::SLASH: return "SLASH";
  case K::COLON: return "COLON";
  case K::COMMA: return "Comma";
  case K::SEMI_COLON: return "Semicolon";
  case K::OPEN_PAREN: return "OPEN_PAREN";
  case K::CLOSE_PAREN: return "CLOSE_PAREN";
  case K::OPEN_BRACE: return "OPEN_BRACE";
  case K::CLOSE_BRACE: return "CLOSE_BRACE";
  case K::IDENTIFIER: return "IDENTIFIER";
  case K::NUMBER_LITERAL: return "NUMBER_LITERAL";
  case K::STRING_LITERAL: return "STRING_LITERAL";
  case K::Space: return "Space";
  case K::EndOfFile: return "EndOfFile";
  }
  return "<UnknownKind>";
}

inline std::string sanitize_text(std::string text, size_t max = 40) {
  for (char &c : text) {
    if (c == '\n')
      c = '~'; // ou '^'
    else if (c == '\t')
      c = '>';
  }

  if (text.size() > max) text = text.substr(0, max) + "...";

  return text;
}

// ================= DUMP TOKEN =================

inline void dump_token(const Token &token) {

  const char *kind = "<no-descriptor>";
  const char *group = "<no-descriptor>";

  if (token.descriptor) {
    kind = token_kind_to_str(token.descriptor->kind);
    group = token_group_to_str(token.descriptor->group);
  }

  std::string text{token.slice.span.view()};

  std::ostringstream oss;
  oss << "Token" << " {\n"
      << "  " << "kind " << ": " << kind << "\n"
      << "  " << "group" << ": " << group << "\n"
      << "  " << "text " << ": \"" << text << "\"\n"
      << "  range : " << token.slice.range.begin.line << ":" << token.slice.range.begin.column << " → " << token.slice.range.end.line << ":" << token.slice.range.end.column << "\n"
      << "  offset: " << token.slice.range.begin.offset << " → " << token.slice.range.end.offset << "\n"
      << "}";

  Console::debug(oss.str());
}

inline void dump_tokens(core::token::TokenStream &tokens) {

  for (auto &token : tokens.get_tokens()) { dump_token(*token); }
}
} // namespace debug::engine
