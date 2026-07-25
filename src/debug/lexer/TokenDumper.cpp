#include "TokenDumper.hpp"
#include "core/token/TokenKind.hpp"
#include <iostream>
#include <sstream>

namespace debug::lexer {

constexpr const char *TokenDumper::token_group_to_str(TokenGroup grp) {
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

std::string TokenDumper::dump(const Token &token) {

  const char *kind = "<no-descriptor>";
  const char *group = "<no-descriptor>";

  if (token.descriptor) {
    kind = token_kind_to_str(token.descriptor->kind);

    group = token_group_to_str(token.descriptor->group);
  }

  std::string text{token.slice.span.view()};

  std::ostringstream oss;

  oss << "Token {\n"
      << "  kind  : " << kind << "\n"
      << "  group : " << group << "\n"
      << "  text  : \"" << sanitize_text(text) << "\"\n"
      << "  range : " << token.slice.range.begin.line << ":" << token.slice.range.begin.column << " -> " << token.slice.range.end.line << ":" << token.slice.range.end.column << "\n"
      << "  offset: " << token.slice.range.begin.offset << " -> " << token.slice.range.end.offset << "\n"
      << "}";

  return oss.str();
}

std::string TokenDumper::dump(const core::token::TokenStream &tokens) {
  std::ostringstream oss;

  for (auto &token : tokens.get_tokens()) { oss << dump(*token) << "\n\n"; }

  return oss.str();
}

} // namespace debug::lexer