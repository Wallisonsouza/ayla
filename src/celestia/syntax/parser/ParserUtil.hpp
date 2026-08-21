#pragma once

#include <vector>

#include "ParserContext.hpp"
#include "celestia/core/token/TokenKind.hpp"
#include "celestia/syntax/parser/ParseStatus.hpp"

namespace celestia::syntax {
class ParseContext;
}

namespace ayla::parser {

inline void consume_statement_separators(celestia::syntax::ParseContext &context) { while (context.tokens().match(TokenKind::NEW_LINE) || context.tokens().match(TokenKind::SEMI_COLON)); }

template <typename ElementType, typename ParseFunc>
celestia::syntax::ParseResult<std::vector<ElementType>>
parse_generic_list(celestia::syntax::ParseContext &context, TokenKind open_token, TokenKind close_token, TokenKind separator_token, ParseFunc parse_element) {
  std::vector<ElementType> elements;

  auto &tokens = context.tokens();

  if (!tokens.check(open_token)) { return celestia::syntax::ParseResult<std::vector<ElementType>>::no_match(); }

  tokens.advance();

  while (!tokens.is_end()) {

    consume_statement_separators(context);

    if (tokens.match(close_token)) { return celestia::syntax::ParseResult<std::vector<ElementType>>::ok(std::move(elements)); }

    auto result = parse_element();

    if (result.is_error()) { return celestia::syntax::ParseResult<std::vector<ElementType>>::fail(result.error().token, result.error().message); }

    if (result.is_no_match()) { return celestia::syntax::ParseResult<std::vector<ElementType>>::fail(tokens.peek(), "expected list element"); }

    elements.push_back(result.value());

    consume_statement_separators(context);

    if (tokens.match(close_token)) { return celestia::syntax::ParseResult<std::vector<ElementType>>::ok(std::move(elements)); }

    if (!tokens.match(separator_token)) { return celestia::syntax::ParseResult<std::vector<ElementType>>::fail(tokens.peek(), "expected list separator"); }
  }

  return celestia::syntax::ParseResult<std::vector<ElementType>>::fail(tokens.peek(), "unterminated list");
}
} // namespace ayla::parser