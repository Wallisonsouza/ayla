#pragma once
#include "ayla-compilation/context.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "language/window/GLFWBackend.hpp"
#include "language/window/module_window.hpp"

namespace ayla::language {

inline ayla::compilation::Context create_context() {

  auto context = ayla::compilation::Context();

  context.backends.set<WindowBackend>(std::make_shared<GLFWBackend>());

  create_module_window(context);

  context.descriptor_table.add(TokenKind::IF_KEYWORD, "if", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::EXTERN_KEYWORD, "extern", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::ELSE_KEYWORD, "else", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::WHILE_KEYWORD, "while", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::FUNCTION_KEYWORD, "funct", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::RETURN_KEYWORD, "return", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::IMPORT_KEYWORD, "import", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::MODULE_KEYWORD, "module", TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::STATIC, "static", TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::MUT, "mut", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::VALUE_KEYWORD, "val", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::PUBLIC, "public", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::PRIVATE, "private", TokenGroup::Keyword);

  // operators
  context.descriptor_table.add(TokenKind::PLUS, "+", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::MINUS, "-", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::STAR, "*", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::SLASH, "/", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::ASSIGN, "=", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::ARROW, "->", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::EQUAL, "==", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::NOT_EQUAL, "!=", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::LESS, "<", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::LESS_EQUAL, "<=", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::GREATER, ">", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::GREATER_EQUAL, ">=", TokenGroup::Operator);

  // precedences
  context.precedence_table.add(TokenKind::ASSIGN, 1, true); // right-associative
  context.precedence_table.add(TokenKind::ARROW, 2, true);  // right-associative
  context.precedence_table.add(TokenKind::EQUAL, 5, false); // left-associative
  context.precedence_table.add(TokenKind::NOT_EQUAL, 5,
                               false);                     // left-associative
  context.precedence_table.add(TokenKind::LESS, 6, false); // left-associative
  context.precedence_table.add(TokenKind::LESS_EQUAL, 6,
                               false); // left-associative
  context.precedence_table.add(TokenKind::GREATER, 6,
                               false); // left-associative
  context.precedence_table.add(TokenKind::GREATER_EQUAL, 6,
                               false);                       // left-associative
  context.precedence_table.add(TokenKind::PLUS, 10, false);  // left-associative
  context.precedence_table.add(TokenKind::MINUS, 10, false); // left-associative
  context.precedence_table.add(TokenKind::STAR, 20, false);  // left-associative
  context.precedence_table.add(TokenKind::SLASH, 20, false);

  // punctuaction
  context.descriptor_table.add(TokenKind::OPEN_PAREN, "(", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::COLON, ":", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::DOT, ".", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::CLOSE_PAREN, ")", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::OPEN_BRACE, "{", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::CLOSE_BRACE, "}", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::OPEN_BRACKET, "[", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::CLOSE_BRACKET, "]", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::SEMI_COLON, ";", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::COMMA, ",", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::SINGLE_QUOTE, "\'", TokenGroup::Punctuation);

  context.descriptor_table.add(TokenKind::IDENTIFIER, TokenGroup::NAME);

  context.descriptor_table.add(TokenKind::NUMBER_LITERAL, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::STRING_LITERAL, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::BoolLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::CharLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::NullLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::NEW_LINE, "\\n", TokenGroup::Whitespace);

  return context;
}
} // namespace ayla::language
