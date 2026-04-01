#pragma once
#include "ayla-compilation/context.hpp"

namespace ayla::language {

inline ayla::compilation::Context create_context() {

  auto context = ayla::compilation::Context();

  context.descriptor_table.add(ayla::structural::token::TokenKind::IF_KEYWORD, "if", ayla::structural::token::TokenGroup::Keyword);
  context.descriptor_table.add(ayla::structural::token::TokenKind::EXTERN_KEYWORD, "extern", ayla::structural::token::TokenGroup::Keyword);
  context.descriptor_table.add(ayla::structural::token::TokenKind::ELSE_KEYWORD, "else", ayla::structural::token::TokenGroup::Keyword);
  context.descriptor_table.add(ayla::structural::token::TokenKind::WHILE_KEYWORD, "while", ayla::structural::token::TokenGroup::Keyword);
  context.descriptor_table.add(ayla::structural::token::TokenKind::FUNCTION_KEYWORD, "funct", ayla::structural::token::TokenGroup::Keyword);
  context.descriptor_table.add(ayla::structural::token::TokenKind::RETURN_KEYWORD, "return", ayla::structural::token::TokenGroup::Keyword);
  context.descriptor_table.add(ayla::structural::token::TokenKind::IMPORT_KEYWORD, "import", ayla::structural::token::TokenGroup::Keyword);
  context.descriptor_table.add(ayla::structural::token::TokenKind::MODULE_KEYWORD, "module", ayla::structural::token::TokenGroup::Keyword);

  context.descriptor_table.add(ayla::structural::token::TokenKind::STATIC, "static", ayla::structural::token::TokenGroup::Keyword);

  context.descriptor_table.add(ayla::structural::token::TokenKind::MUT, "mut", ayla::structural::token::TokenGroup::Keyword);
  context.descriptor_table.add(ayla::structural::token::TokenKind::VALUE_KEYWORD, "val", ayla::structural::token::TokenGroup::Keyword);
  context.descriptor_table.add(ayla::structural::token::TokenKind::PUBLIC, "public", ayla::structural::token::TokenGroup::Keyword);
  context.descriptor_table.add(ayla::structural::token::TokenKind::PRIVATE, "private", ayla::structural::token::TokenGroup::Keyword);

  // operators
  context.descriptor_table.add(ayla::structural::token::TokenKind::PLUS, "+", ayla::structural::token::TokenGroup::Operator);
  context.descriptor_table.add(ayla::structural::token::TokenKind::MINUS, "-", ayla::structural::token::TokenGroup::Operator);
  context.descriptor_table.add(ayla::structural::token::TokenKind::STAR, "*", ayla::structural::token::TokenGroup::Operator);
  context.descriptor_table.add(ayla::structural::token::TokenKind::SLASH, "/", ayla::structural::token::TokenGroup::Operator);
  context.descriptor_table.add(ayla::structural::token::TokenKind::ASSIGN, "=", ayla::structural::token::TokenGroup::Operator);
  context.descriptor_table.add(ayla::structural::token::TokenKind::ARROW, "->", ayla::structural::token::TokenGroup::Operator);
  context.descriptor_table.add(ayla::structural::token::TokenKind::EQUAL, "==", ayla::structural::token::TokenGroup::Operator);
  context.descriptor_table.add(ayla::structural::token::TokenKind::NOT_EQUAL, "!=", ayla::structural::token::TokenGroup::Operator);
  context.descriptor_table.add(ayla::structural::token::TokenKind::LESS, "<", ayla::structural::token::TokenGroup::Operator);
  context.descriptor_table.add(ayla::structural::token::TokenKind::LESS_EQUAL, "<=", ayla::structural::token::TokenGroup::Operator);
  context.descriptor_table.add(ayla::structural::token::TokenKind::GREATER, ">", ayla::structural::token::TokenGroup::Operator);
  context.descriptor_table.add(ayla::structural::token::TokenKind::GREATER_EQUAL, ">=", ayla::structural::token::TokenGroup::Operator);

  // precedences
  context.precedence_table.add(ayla::structural::token::TokenKind::ASSIGN, 1, true); // right-associative
  context.precedence_table.add(ayla::structural::token::TokenKind::ARROW, 2, true);  // right-associative
  context.precedence_table.add(ayla::structural::token::TokenKind::EQUAL, 5, false); // left-associative
  context.precedence_table.add(ayla::structural::token::TokenKind::NOT_EQUAL, 5,
                               false);                                              // left-associative
  context.precedence_table.add(ayla::structural::token::TokenKind::LESS, 6, false); // left-associative
  context.precedence_table.add(ayla::structural::token::TokenKind::LESS_EQUAL, 6,
                               false); // left-associative
  context.precedence_table.add(ayla::structural::token::TokenKind::GREATER, 6,
                               false); // left-associative
  context.precedence_table.add(ayla::structural::token::TokenKind::GREATER_EQUAL, 6,
                               false);                                                // left-associative
  context.precedence_table.add(ayla::structural::token::TokenKind::PLUS, 10, false);  // left-associative
  context.precedence_table.add(ayla::structural::token::TokenKind::MINUS, 10, false); // left-associative
  context.precedence_table.add(ayla::structural::token::TokenKind::STAR, 20, false);  // left-associative
  context.precedence_table.add(ayla::structural::token::TokenKind::SLASH, 20, false);

  // punctuaction
  context.descriptor_table.add(ayla::structural::token::TokenKind::OPEN_PAREN, "(", ayla::structural::token::TokenGroup::Punctuation);
  context.descriptor_table.add(ayla::structural::token::TokenKind::COLON, ":", ayla::structural::token::TokenGroup::Punctuation);
  context.descriptor_table.add(ayla::structural::token::TokenKind::DOT, ".", ayla::structural::token::TokenGroup::Punctuation);
  context.descriptor_table.add(ayla::structural::token::TokenKind::CLOSE_PAREN, ")", ayla::structural::token::TokenGroup::Punctuation);
  context.descriptor_table.add(ayla::structural::token::TokenKind::OPEN_BRACE, "{", ayla::structural::token::TokenGroup::Punctuation);
  context.descriptor_table.add(ayla::structural::token::TokenKind::CLOSE_BRACE, "}", ayla::structural::token::TokenGroup::Punctuation);
  context.descriptor_table.add(ayla::structural::token::TokenKind::OPEN_BRACKET, "[", ayla::structural::token::TokenGroup::Punctuation);
  context.descriptor_table.add(ayla::structural::token::TokenKind::CLOSE_BRACKET, "]", ayla::structural::token::TokenGroup::Punctuation);
  context.descriptor_table.add(ayla::structural::token::TokenKind::SEMI_COLON, ";", ayla::structural::token::TokenGroup::Punctuation);
  context.descriptor_table.add(ayla::structural::token::TokenKind::COMMA, ",", ayla::structural::token::TokenGroup::Punctuation);
  context.descriptor_table.add(ayla::structural::token::TokenKind::SINGLE_QUOTE, "\'", ayla::structural::token::TokenGroup::Punctuation);

  context.descriptor_table.add(ayla::structural::token::TokenKind::IDENTIFIER, ayla::structural::token::TokenGroup::NAME);

  context.descriptor_table.add(ayla::structural::token::TokenKind::NUMBER_LITERAL, ayla::structural::token::TokenGroup::Literal);
  context.descriptor_table.add(ayla::structural::token::TokenKind::STRING_LITERAL, ayla::structural::token::TokenGroup::Literal);
  context.descriptor_table.add(ayla::structural::token::TokenKind::BoolLiteral, ayla::structural::token::TokenGroup::Literal);
  context.descriptor_table.add(ayla::structural::token::TokenKind::CharLiteral, ayla::structural::token::TokenGroup::Literal);
  context.descriptor_table.add(ayla::structural::token::TokenKind::NullLiteral, ayla::structural::token::TokenGroup::Literal);
  context.descriptor_table.add(ayla::structural::token::TokenKind::NEW_LINE, "\\n", ayla::structural::token::TokenGroup::Whitespace);

  return context;
}
} // namespace ayla::language
