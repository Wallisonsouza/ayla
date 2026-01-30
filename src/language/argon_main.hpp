#pragma once
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/language_context.hpp"
#include "language/module_console.hpp"

namespace ayla::language {

inline LanguageContext create_context() {

  auto context = LanguageContext();

  auto parent = context.modules.create_module("debug");
  ayla::modules::create_module_console(context, parent);
  ayla::modules::create_module_math(context);

  context.precedence_table.add(TokenKind::Assign, 1, true);
  context.precedence_table.add(TokenKind::Equals, 5, false);

  context.descriptor_table.add(TokenKind::LessThan, "<", TokenGroup::Operator);
  context.precedence_table.add(TokenKind::LessThan, 6, false);

  context.precedence_table.add(TokenKind::Plus, 10, false);
  context.precedence_table.add(TokenKind::Minus, 10, false);
  context.precedence_table.add(TokenKind::Star, 20, false);
  context.precedence_table.add(TokenKind::Slash, 20, false);

  // context.precedence_table.add(TokenKind::NotEqual, 5, false);     // !=

  // context.precedence_table.add(TokenKind::LessEqual, 6, false);    // <=
  // context.precedence_table.add(TokenKind::Greater, 6, false);      // >
  // context.precedence_table.add(TokenKind::GreaterEqual, 6, false); // >=

  context.descriptor_table.add(TokenKind::IF_KEYWORD, "if", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::ELSE_KEYWORD, "else", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::WHILE_KEYWORD, "while", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::FUNCTION_KEYWORD, "funct", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::RETURN_KEYWORD, "return", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::IMPORT_KEYWORD, "import", TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::STATIC, "static", TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::MUT, "mut", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::VALUE_KEYWORD, "val", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::PUBLIC, "public", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::PRIVATE, "private", TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::Plus, "+", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Minus, "-", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Star, "*", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Slash, "/", TokenGroup::Operator);

  context.descriptor_table.add(TokenKind::Assign, "=", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Arrow, "->", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Equals, "==", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Ternary, "?", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::GreaterThan, ">", TokenGroup::Operator);

  context.descriptor_table.add(TokenKind::OPEN_PAREN, "(", TokenGroup::Punctuation);

  context.descriptor_table.add(TokenKind::COLON, ":", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::Dot, ".", TokenGroup::Punctuation);
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
