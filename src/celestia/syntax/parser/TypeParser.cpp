#include "TypeParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"

#include "celestia/ast/types/Array.hpp"
#include "celestia/ast/types/FunctionType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/ast/types/ReferenceType.hpp"

#include "celestia/syntax/parser/ParseStatus.hpp"
#include "celestia/syntax/parser/ParserUtil.hpp"

namespace celestia::syntax {

TypeParser::TypeParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

ParseResult<ast::TypeNode *> TypeParser::parse_type() {

  auto &tokens = context.tokens();

  switch (tokens.peek()->kind()) {

  case TokenKind::REF_KEYWORD: return parse_reference_type();

  case TokenKind::OPEN_BRACKET: return parse_array_type();

  case TokenKind::OPEN_PAREN: return parse_function_type();

  case TokenKind::IDENTIFIER: return parse_named_type();

  default: return ParseResult<ast::TypeNode *>::no_match();
  }
}

ParseResult<ast::TypeNode *> TypeParser::parse_named_type() {

  auto name = parser.names().parse_name();

  if (!name) { return ParseResult<ast::TypeNode *>::fail(context.tokens().peek(), "expected type name"); }

  auto *type = context.get_ast().create_node<ast::NamedType>(name);

  return ParseResult<ast::TypeNode *>::ok(type);
}

ParseResult<ast::TypeNode *> TypeParser::parse_array_type() {

  auto &tokens = context.tokens();

  if (!tokens.check(TokenKind::OPEN_BRACKET)) { return ParseResult<ast::TypeNode *>::no_match(); }

  tokens.advance();

  auto element_result = parse_type();

  if (element_result.is_error()) { return ParseResult<ast::TypeNode *>::fail(element_result.error().token, element_result.error().message); }

  if (element_result.is_no_match()) { return ParseResult<ast::TypeNode *>::fail(tokens.peek(), "expected array element type"); }

  if (!tokens.match(TokenKind::CLOSE_BRACKET)) { return ParseResult<ast::TypeNode *>::fail(tokens.peek(), "expected ']'"); }

  auto *type = context.get_ast().create_node<ast::ArrayType>(element_result.value());

  return ParseResult<ast::TypeNode *>::ok(type);
}

ParseResult<ast::TypeNode *> TypeParser::parse_reference_type() {

  auto &tokens = context.tokens();

  if (!tokens.check(TokenKind::REF_KEYWORD)) { return ParseResult<ast::TypeNode *>::no_match(); }

  tokens.advance();

  if (!tokens.match(TokenKind::LESS)) { return ParseResult<ast::TypeNode *>::fail(tokens.peek(), "expected '<' after 'ref'"); }

  auto target_result = parse_type();

  if (target_result.is_error()) { return ParseResult<ast::TypeNode *>::fail(target_result.error().token, target_result.error().message); }

  if (target_result.is_no_match()) { return ParseResult<ast::TypeNode *>::fail(tokens.peek(), "expected reference target type"); }

  if (!tokens.match(TokenKind::GREATER)) { return ParseResult<ast::TypeNode *>::fail(tokens.peek(), "expected '>' after reference type"); }

  auto *type = context.get_ast().create_node<ast::ReferenceType>(target_result.value());

  return ParseResult<ast::TypeNode *>::ok(type);
}

ParseResult<ast::TypeNode *> TypeParser::parse_function_type() {

  auto &tokens = context.tokens();

  if (!tokens.check(TokenKind::OPEN_PAREN)) { return ParseResult<ast::TypeNode *>::no_match(); }

  auto parameters = ayla::parser::parse_generic_list<ast::TypeNode *>(context, TokenKind::OPEN_PAREN, TokenKind::CLOSE_PAREN, TokenKind::COMMA, [&]() { return parse_type(); });

  if (parameters.is_error()) { return ParseResult<ast::TypeNode *>::fail(parameters.error().token, parameters.error().message); }

  if (parameters.is_no_match()) { return ParseResult<ast::TypeNode *>::fail(tokens.peek(), "expected function parameters"); }

  if (!tokens.match(TokenKind::ARROW)) { return ParseResult<ast::TypeNode *>::fail(tokens.peek(), "expected '->' after function parameters"); }

  auto return_result = parse_type();

  if (return_result.is_error()) { return ParseResult<ast::TypeNode *>::fail(return_result.error().token, return_result.error().message); }

  if (return_result.is_no_match()) { return ParseResult<ast::TypeNode *>::fail(tokens.peek(), "expected function return type"); }

  auto *type = context.get_ast().create_node<ast::FunctionType>(std::move(parameters.value()), return_result.value());

  return ParseResult<ast::TypeNode *>::ok(type);
}

} // namespace celestia::syntax