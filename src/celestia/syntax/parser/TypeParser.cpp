#include "TypeParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"

#include "celestia/ast/types/FunctionType.hpp"
#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/diagnostic/Diagnostic.hpp"
#include "celestia/diagnostic/DiagnosticCode.hpp"
#include "celestia/syntax/parser/ParseStatus.hpp"

namespace celestia::syntax {

static void report_expected(ParseContext &context, diagnostic::DiagnosticCode code, TokenKind expected) {

  auto &tokens = context.tokens();
  auto *token = tokens.current();

  context.unit.diagnostics.report({
      .severity = diagnostic::Severity::Error,
      .code = code,
      .arguments =
          {
              diagnostic::found(token->kind()),
              diagnostic::expected(expected),
          },
      .labels =
          {
              diagnostic::location(token->slice),
          },
  });
}

static void report_expected_type(ParseContext &context) {

  auto &tokens = context.tokens();
  auto *token = tokens.current();

  context.unit.diagnostics.report({
      .severity = diagnostic::Severity::Error,
      .code = diagnostic::DiagnosticCode::ExpectedType,
      .arguments =
          {
              diagnostic::found(token->kind()),
          },
      .labels =
          {
              diagnostic::location(token->slice),
          },
  });
}

TypeParser::TypeParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

ParseResult<ast::TypeNode *> TypeParser::parse_type() {

  auto &tokens = context.tokens();

  switch (tokens.kind()) {

  case TokenKind::OPEN_PAREN: return parse_function_type();

  case TokenKind::IDENTIFIER:

    if (tokens.check(TokenKind::LESS, 1)) { return parse_generic_type(); }

    return parse_named_type();

  default: return ParseResult<ast::TypeNode *>::no_match();
  }
}

ParseResult<ast::TypeNode *> TypeParser::parse_named_type() {

  auto &tokens = context.tokens();

  auto *name = parser.names().parse_name();

  if (!name) {
    report_expected_type(context);
    return ParseResult<ast::TypeNode *>::fail();
  }

  auto *type = context.get_ast().alloc<ast::NamedType>(name);

  return ParseResult<ast::TypeNode *>::ok(type);
}

ParseResult<ast::TypeNode *> TypeParser::parse_generic_type() {

  auto &tokens = context.tokens();

  auto *name = parser.names().parse_name();

  if (!name) {
    report_expected_type(context);
    return ParseResult<ast::TypeNode *>::fail();
  }

  // Type<
  if (!tokens.match(TokenKind::LESS)) {

    report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, TokenKind::LESS);

    return ParseResult<ast::TypeNode *>::fail();
  }

  std::vector<ast::TypeNode *> arguments;

  tokens.skip_trivia();

  // Type<>
  if (tokens.match(TokenKind::GREATER)) {

    report_expected_type(context);

    return ParseResult<ast::TypeNode *>::fail();
  }

  while (!tokens.is_end()) {

    // Type<int, ...>
    auto result = parse_type();

    // O parser interno já gerou o diagnóstico.
    if (result.is_error()) { return ParseResult<ast::TypeNode *>::fail(); }

    // Aqui um tipo é obrigatório.
    if (result.is_no_match()) {

      report_expected_type(context);

      return ParseResult<ast::TypeNode *>::fail();
    }

    arguments.push_back(result.value());

    tokens.skip_trivia();

    // Type<int>
    if (tokens.match(TokenKind::GREATER)) {
      auto *type = context.get_ast().alloc<ast::GenericTypeNode>(name, std::move(arguments));

      return ParseResult<ast::TypeNode *>::ok(type);
    }

    // Type<int, ...>
    if (!tokens.match(TokenKind::COMMA)) {

      report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, TokenKind::GREATER);

      return ParseResult<ast::TypeNode *>::fail();
    }

    tokens.skip_trivia();

    // Type<int,>
    if (tokens.match(TokenKind::GREATER)) {

      report_expected_type(context);

      return ParseResult<ast::TypeNode *>::fail();
    }
  }

  // Type<int EOF
  report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, TokenKind::GREATER);

  return ParseResult<ast::TypeNode *>::fail();
}

ParseResult<ast::TypeNode *> TypeParser::parse_function_type() {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::OPEN_PAREN)) { return ParseResult<ast::TypeNode *>::no_match(); }

  std::vector<ast::TypeNode *> parameters;

  tokens.skip_trivia();

  // () -> Type
  if (!tokens.match(TokenKind::CLOSE_PAREN)) {

    while (!tokens.is_end()) {

      // (Type, ...)
      auto result = parse_type();

      if (result.is_error()) { return ParseResult<ast::TypeNode *>::fail(); }

      // (Type, ...)
      if (result.is_no_match()) {

        report_expected_type(context);

        return ParseResult<ast::TypeNode *>::fail();
      }

      parameters.push_back(result.value());

      tokens.skip_trivia();

      // (Type)
      if (tokens.match(TokenKind::CLOSE_PAREN)) { break; }

      // (Type, ...)
      if (!tokens.match(TokenKind::COMMA)) {

        report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, TokenKind::COMMA);

        return ParseResult<ast::TypeNode *>::fail();
      }

      tokens.skip_trivia();

      // (Type,)
      if (tokens.match(TokenKind::CLOSE_PAREN)) { break; }
    }

    if (tokens.is_end()) {

      report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, TokenKind::CLOSE_PAREN);

      return ParseResult<ast::TypeNode *>::fail();
    }
  }

  // () ...
  if (!tokens.match(TokenKind::ARROW)) {

    report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, TokenKind::ARROW);

    return ParseResult<ast::TypeNode *>::fail();
  }

  // () -> ...
  auto return_result = parse_type();

  if (return_result.is_error()) { return ParseResult<ast::TypeNode *>::fail(); }

  if (return_result.is_no_match()) {

    report_expected_type(context);

    return ParseResult<ast::TypeNode *>::fail();
  }

  auto *type = context.get_ast().alloc<ast::FunctionType>(std::move(parameters), return_result.value());

  return ParseResult<ast::TypeNode *>::ok(type);
}

} // namespace celestia::syntax