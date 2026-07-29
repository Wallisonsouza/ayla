#pragma once

#include "core/operators/BinaryOperation.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/LangContext.hpp"
#include "semantic/checker/TypeChecker.hpp"
#include "semantic/types/type.hpp"
#include <memory>

namespace ayla::language {

inline LanguageContext create_context() {

  auto context = LanguageContext();

  context.type_table["number"] = std::make_shared<Type>(BuiltinTypes::Number);

  context.type_table["string"] = std::make_shared<Type>(BuiltinTypes::String);

  context.type_table["bool"] = std::make_shared<Type>(BuiltinTypes::Boolean);

  context.type_table["void"] = std::make_shared<Type>(BuiltinTypes::Void);

  //infix
  context.operators.add_infix(TokenKind::ASSIGN, 1, core::table::Associativity::Right, BinaryOperation::Assign);
  context.operators.add_infix(TokenKind::ARROW, 2, core::table::Associativity::Right, BinaryOperation::Arrow);
  context.operators.add_infix(TokenKind::EQUAL, 5, core::table::Associativity::Left, BinaryOperation::Equal);
  context.operators.add_infix(TokenKind::NOT_EQUAL, 5, core::table::Associativity::Left, BinaryOperation::NotEqual);
  context.operators.add_infix(TokenKind::LESS, 6, core::table::Associativity::Left, BinaryOperation::Less);
  context.operators.add_infix(TokenKind::LESS_EQUAL, 6, core::table::Associativity::Left, BinaryOperation::LessEqual);
  context.operators.add_infix(TokenKind::GREATER, 6, core::table::Associativity::Left, BinaryOperation::Greater);
  context.operators.add_infix(TokenKind::GREATER_EQUAL, 6, core::table::Associativity::Left, BinaryOperation::GreaterEqual);
  context.operators.add_infix(TokenKind::PLUS, 10, core::table::Associativity::Left, BinaryOperation::Add);
  context.operators.add_infix(TokenKind::MINUS, 10, core::table::Associativity::Left, BinaryOperation::Subtract);
  context.operators.add_infix(TokenKind::STAR, 20, core::table::Associativity::Left, BinaryOperation::Multiply);
  context.operators.add_infix(TokenKind::SLASH, 20, core::table::Associativity::Left, BinaryOperation::Divide);
 
  //prefix
  context.operators.add_prefix(TokenKind::NOT, 30, UnaryOperation::Not);
  // context.operators.add_prefix(TokenKind::MINUS, 30, UnaryOperation::Negate);
  // context.operators.add_prefix(TokenKind::PLUS, 30, UnaryOperation::Positive);

  //postfix
  context.operators.add_postfix(TokenKind::OPEN_PAREN, 100, PostfixOperation::Call);
  context.operators.add_postfix(TokenKind::OPEN_BRACKET, 100, PostfixOperation::IndexAccess);
  context.operators.add_postfix(TokenKind::DOT, 100, PostfixOperation::MemberAccess);

  //keywords
  context.descriptors.add(TokenKind::TRUE, "true", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::FALSE, "false", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::IF_KEYWORD, "if", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::EXTERN, "extern", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::ELSE_KEYWORD, "else", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::WHILE_KEYWORD, "while", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::FUNCTION_KEYWORD, "fu", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::RETURN_KEYWORD, "return", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::IMPORT_KEYWORD, "import", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::MODULE_KEYWORD, "module", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::STATIC, "static", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::MUT, "mut", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::VALUE_KEYWORD, "val", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::PUBLIC, "public", TokenGroup::Keyword);
  context.descriptors.add(TokenKind::PRIVATE, "private", TokenGroup::Keyword);

  // operators
  context.descriptors.add(TokenKind::NOT, "!", TokenGroup::Operator);
  context.descriptors.add(TokenKind::PLUS, "+", TokenGroup::Operator);
  context.descriptors.add(TokenKind::MINUS, "-", TokenGroup::Operator);
  context.descriptors.add(TokenKind::STAR, "*", TokenGroup::Operator);
  context.descriptors.add(TokenKind::SLASH, "/", TokenGroup::Operator);
  context.descriptors.add(TokenKind::ASSIGN, "=", TokenGroup::Operator);
  context.descriptors.add(TokenKind::ARROW, "->", TokenGroup::Operator);
  context.descriptors.add(TokenKind::EQUAL, "==", TokenGroup::Operator);
  context.descriptors.add(TokenKind::NOT_EQUAL, "!=", TokenGroup::Operator);
  context.descriptors.add(TokenKind::LESS, "<", TokenGroup::Operator);
  context.descriptors.add(TokenKind::LESS_EQUAL, "<=", TokenGroup::Operator);
  context.descriptors.add(TokenKind::GREATER, ">", TokenGroup::Operator);
  context.descriptors.add(TokenKind::GREATER_EQUAL, ">=", TokenGroup::Operator);

  // punctuaction
  context.descriptors.add(TokenKind::OPEN_PAREN, "(", TokenGroup::Punctuation);
  context.descriptors.add(TokenKind::COLON, ":", TokenGroup::Punctuation);
  context.descriptors.add(TokenKind::DOT, ".", TokenGroup::Punctuation);
  context.descriptors.add(TokenKind::CLOSE_PAREN, ")", TokenGroup::Punctuation);
  context.descriptors.add(TokenKind::OPEN_BRACE, "{", TokenGroup::Punctuation);
  context.descriptors.add(TokenKind::CLOSE_BRACE, "}", TokenGroup::Punctuation);
  context.descriptors.add(TokenKind::OPEN_BRACKET, "[", TokenGroup::Punctuation);
  context.descriptors.add(TokenKind::CLOSE_BRACKET, "]", TokenGroup::Punctuation);
  context.descriptors.add(TokenKind::SEMI_COLON, ";", TokenGroup::Punctuation);
  context.descriptors.add(TokenKind::COMMA, ",", TokenGroup::Punctuation);
  context.descriptors.add(TokenKind::SINGLE_QUOTE, "\'", TokenGroup::Punctuation);

  context.descriptors.add(TokenKind::IDENTIFIER, TokenGroup::NAME);
  context.descriptors.add(TokenKind::NUMBER_LITERAL, TokenGroup::Literal);
  context.descriptors.add(TokenKind::STRING_LITERAL, TokenGroup::Literal);
  context.descriptors.add(TokenKind::CharLiteral, TokenGroup::Literal);
  context.descriptors.add(TokenKind::NullLiteral, TokenGroup::Literal);
  context.descriptors.add(TokenKind::NEW_LINE, "\\n", TokenGroup::Whitespace);

  return context;
}
} // namespace ayla::language
