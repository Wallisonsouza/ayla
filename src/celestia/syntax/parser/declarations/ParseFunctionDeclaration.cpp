#include "celestia/semantic/resolver/Trace.hpp"
#include "celestia/syntax/parser/DeclarationParser.hpp"
#include "celestia/syntax/parser/ParserContext.hpp"
#include "celestia/syntax/parser/PatternParser.hpp"
#include "celestia/syntax/parser/StatementParser.hpp"
#include "celestia/syntax/parser/TypeParser.hpp"

namespace celestia::syntax {

static void report_expected_pattern(ParseContext &context) {

  auto &tokens = context.tokens();

  context.unit.diagnostics.report({
      .severity = diagnostic::Severity::Error,
      .code = diagnostic::DiagnosticCode::ExpectedPattern,
      .arguments =
          {
              diagnostic::found(tokens.kind()),
          },
      .labels =
          {
              diagnostic::location(tokens.diagnostic_slice()),
          },
  });
}

static void report_expected_type(ParseContext &context) {

  auto &tokens = context.tokens();

  context.unit.diagnostics.report({
      .severity = diagnostic::Severity::Error,
      .code = diagnostic::DiagnosticCode::ExpectedType,
      .arguments =
          {
              diagnostic::found(tokens.kind()),
          },
      .labels =
          {
              diagnostic::location(tokens.diagnostic_slice()),
          },
  });
}

ast::FunctionDeclaration *DeclarationParser::parse_function_declaration(DeclarationSpecifiers specifiers, bool require_body) {

  auto &tokens = context.tokens();

  debug::trace(debug::Category::Parser, "parsing function declaration");

  // fun
  if (!tokens.match(TokenKind::FUN_KEYWORD)) { return nullptr; }

  debug::trace(debug::Category::Parser, "function keyword found");

  // name
  auto *name = parser.names().parse_name();

  if (!name) {
    report_expected(context, diagnostic::DiagnosticCode::ExpectedIdentifier, TokenKind::IDENTIFIER);

    return nullptr;
  }

  // fun<T, U>
  auto generic_parameters = parse_delimited_list<ast::IdentifierNode *>(context, TokenKind::LESS, TokenKind::GREATER, TokenKind::COMMA, [&]() -> ParseResult<ast::IdentifierNode *> {
    auto *generic = parser.names().parse_name();

    if (!generic) {
      report_expected(context, diagnostic::DiagnosticCode::ExpectedIdentifier, TokenKind::IDENTIFIER);

      return ParseResult<ast::IdentifierNode *>::fail();
    }

    return ParseResult<ast::IdentifierNode *>::ok(generic);
  });

  if (generic_parameters.is_error()) {
    debug::trace(debug::Category::Parser, "error in generic params");

    return nullptr;
  }

  // fun(...)
  if (!tokens.check(TokenKind::OPEN_PAREN)) {

    report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, TokenKind::OPEN_PAREN);

    return nullptr;
  }

  // fun(a: Int, b: Int)
  auto parameters = parse_delimited_list<ast::PatternNode *>(context, TokenKind::OPEN_PAREN, TokenKind::CLOSE_PAREN, TokenKind::COMMA, [&]() -> ParseResult<ast::PatternNode *> {
    auto result = parser.patterns().parse_pattern();

    if (result.is_error()) { return ParseResult<ast::PatternNode *>::fail(); }

    if (result.is_no_match()) {
      report_expected_pattern(context);

      return ParseResult<ast::PatternNode *>::fail();
    }

    return result;
  });

  if (parameters.is_error()) { return nullptr; }

  ast::TypeNode *return_type = nullptr;

  // -> Type
  if (tokens.match(TokenKind::ARROW)) {

    auto result = parser.types().parse_type();

    if (result.is_error()) { return nullptr; }

    if (result.is_no_match()) {
      report_expected_type(context);

      return nullptr;
    }

    return_type = result.value();
  }

  ast::BlockStatement *body = nullptr;

  // { ... }
  if (tokens.check(TokenKind::OPEN_BRACE)) {

    body = parser.statements().parse_block_statement();

    if (!body) { return nullptr; }

  } else if (require_body) {

    report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, TokenKind::OPEN_BRACE);

    return nullptr;
  }

  debug::trace(debug::Category::Parser, "creating FunctionDeclaration");

  return context.get_ast().alloc<ast::FunctionDeclaration>(name, std::move(generic_parameters.value()), std::move(parameters.value()), return_type, body, specifiers);
}
} // namespace celestia::syntax