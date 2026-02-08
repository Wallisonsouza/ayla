#pragma once
#include "core/node/BinaryOp.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/language_context.hpp"
#include "stdlib/Console.hpp"
#include "stdlib/Glfw.hpp"

namespace ayla::language {

inline LanguageContext create_context() {

  auto context = LanguageContext();

  create_module_console(context);
  create_module_glfw(context);

  context.descriptor_table.add(TokenKind::TRUE_KEYWORD, "true", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::FALSE_KEYWORD, "false", TokenGroup::Keyword);
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
  context.descriptor_table.add(TokenKind::NOT, "!", TokenGroup::Operator);
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

  context.precedence_table.add_right(TokenKind::ASSIGN, 1, ast::BinaryOperation::Assign);
  context.precedence_table.add_right(TokenKind::ARROW, 2, ast::BinaryOperation::Arrow);

  context.precedence_table.add_left(TokenKind::EQUAL, 5, ast::BinaryOperation::Equal);
  context.precedence_table.add_left(TokenKind::NOT_EQUAL, 5, ast::BinaryOperation::NotEqual);
  context.precedence_table.add_left(TokenKind::LESS, 6, ast::BinaryOperation::Less);
  context.precedence_table.add_left(TokenKind::LESS_EQUAL, 6, ast::BinaryOperation::LessEqual);
  context.precedence_table.add_left(TokenKind::GREATER, 6, ast::BinaryOperation::Greater);
  context.precedence_table.add_left(TokenKind::GREATER_EQUAL, 6, ast::BinaryOperation::GreaterEqual);

  // additive
  context.precedence_table.add_left(TokenKind::PLUS, 10, ast::BinaryOperation::Add);
  context.precedence_table.add_left(TokenKind::MINUS, 10, ast::BinaryOperation::Subtract);
  context.precedence_table.add_left(TokenKind::STAR, 20, ast::BinaryOperation::Multiply);
  context.precedence_table.add_left(TokenKind::SLASH, 20, ast::BinaryOperation::Divide);

  
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
  context.descriptor_table.add(TokenKind::CharLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::NullLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::NEW_LINE, "\\n", TokenGroup::Whitespace);

  return context;
}
} // namespace ayla::language
