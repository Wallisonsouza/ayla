#include "PatternParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"
#include "TypeParser.hpp"

#include "celestia/ast/patterns/NamedPatternNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/core/token/token_stream.hpp"

namespace celestia::syntax {

PatternParser::PatternParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

ParseResult<ast::PatternNode *> PatternParser::parse_pattern() {

  auto *current = context.tokens().current();

  if (!current) { return ParseResult<ast::PatternNode *>::no_match(); }

  switch (current->desc->kind) {

  case TokenKind::IDENTIFIER:
    return parse_identifier_pattern();

    // case TokenKind::OPEN_BRACKET:
    //     return parse_array_pattern();

    // case TokenKind::OPEN_BRACE:
    //     return parse_object_pattern();

  default: return ParseResult<ast::PatternNode *>::no_match();
  }
}

ParseResult<ast::PatternNode *> PatternParser::parse_identifier_pattern() {

  auto *name = parser.names().parse_name();

  if (!name) { return ParseResult<ast::PatternNode *>::fail(context.tokens().current(), "expected pattern name"); }

  ast::TypeNode *type = nullptr;

  if (context.tokens().match(TokenKind::COLON)) {

    auto type_result = parser.types().parse_type();

    if (type_result.is_error()) { return ParseResult<ast::PatternNode *>::fail(type_result.error().token, type_result.error().message); }

    if (type_result.is_no_match()) { return ParseResult<ast::PatternNode *>::fail(context.tokens().current(), "expected pattern type"); }

    type = type_result.value();
  }

  auto *pattern = context.get_ast().alloc<ast::NamedPattern>(name, type);

  return ParseResult<ast::PatternNode *>::ok(pattern);
}

ParseResult<ast::PatternNode *> PatternParser::parse_typed_pattern() { return ParseResult<ast::PatternNode *>::no_match(); }

} // namespace celestia::syntax