#include "TypeParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"

#include "celestia/ast/types/FunctionType.hpp"
#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/syntax/parser/ParseStatus.hpp"
#include "celestia/syntax/parser/ParserUtil.hpp"

namespace celestia::syntax {

TypeParser::TypeParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

ParseResult<ast::TypeNode *> TypeParser::parse_type() {

  auto &tokens = context.tokens();

  switch (tokens.kind()) {

  case TokenKind::OPEN_PAREN: return parse_function_type();

  case TokenKind::IDENTIFIER:

    if (tokens.check(TokenKind::LESS, 1)) return parse_generic_type();

    return parse_named_type();

  default: return ParseResult<ast::TypeNode *>::no_match();
  }
}

ParseResult<ast::TypeNode *> TypeParser::parse_named_type() {

  auto name = parser.names().parse_name();

  if (!name) { return ParseResult<ast::TypeNode *>::fail(context.tokens().current(), "expected type name"); }

  auto *type = context.get_ast().alloc<ast::NamedType>(name);

  return ParseResult<ast::TypeNode *>::ok(type);
}

ParseResult<ast::TypeNode *> TypeParser::parse_generic_type() {

  auto &tokens = context.tokens();

  auto name = parser.names().parse_name();

  if (!name) { return ParseResult<ast::TypeNode *>::fail(tokens.current(), "expected generic type name"); }

  if (!tokens.match(TokenKind::LESS)) { return ParseResult<ast::TypeNode *>::fail(tokens.current(), "expected '<'"); }

  std::vector<ast::TypeNode *> arguments;

  while (true) {

    auto argument = parse_type();

    if (argument.is_error()) return ParseResult<ast::TypeNode *>::fail(argument.error().token, argument.error().message);

    if (argument.is_no_match()) return ParseResult<ast::TypeNode *>::fail(tokens.current(), "expected generic argument");

    arguments.push_back(argument.value());

    if (!tokens.match(TokenKind::COMMA)) break;
  }

  if (!tokens.match(TokenKind::GREATER)) { return ParseResult<ast::TypeNode *>::fail(tokens.current(), "expected '>'"); }

  auto *type = context.get_ast().alloc<ast::GenericTypeNode>(name, std::move(arguments));

  return ParseResult<ast::TypeNode *>::ok(type);
}

ParseResult<ast::TypeNode *> TypeParser::parse_function_type() {

  auto &tokens = context.tokens();

  if (!tokens.check(TokenKind::OPEN_PAREN)) { return ParseResult<ast::TypeNode *>::no_match(); }

  auto parameters = ayla::parser::parse_generic_list<ast::TypeNode *>(context, TokenKind::OPEN_PAREN, TokenKind::CLOSE_PAREN, TokenKind::COMMA, [&]() { return parse_type(); });

  if (parameters.is_error()) { return ParseResult<ast::TypeNode *>::fail(parameters.error().token, parameters.error().message); }

  if (parameters.is_no_match()) { return ParseResult<ast::TypeNode *>::fail(tokens.current(), "expected function parameters"); }

  if (!tokens.match(TokenKind::ARROW)) { return ParseResult<ast::TypeNode *>::fail(tokens.current(), "expected '->' after function parameters"); }

  auto return_result = parse_type();

  if (return_result.is_error()) { return ParseResult<ast::TypeNode *>::fail(return_result.error().token, return_result.error().message); }

  if (return_result.is_no_match()) { return ParseResult<ast::TypeNode *>::fail(tokens.current(), "expected function return type"); }

  auto *type = context.get_ast().alloc<ast::FunctionType>(std::move(parameters.value()), return_result.value());

  return ParseResult<ast::TypeNode *>::ok(type);
}

} // namespace celestia::syntax