#pragma once

#include <vector>

#include "ParserContext.hpp"
#include "core/token/TokenKind.hpp"

class ParseContext;

namespace ayla::parser {

inline void consume_statement_separators(ParseContext &context) { while (context.tokens().match(TokenKind::NEW_LINE) || context.tokens().match(TokenKind::SEMI_COLON)); }

template <typename ElementType, typename ParseFunc>
std::vector<ElementType *> parse_generic_list(ParseContext &context, TokenKind open_token, TokenKind close_token, TokenKind separator_token, ParseFunc parse_element) {
  std::vector<ElementType *> elements;

  auto &tokens = context.tokens();

  if (!tokens.match(open_token)) {
    // context.//report_error(
    //     DiagnosticCode::ExpectedToken,
    //     "opening token"
    // );

    return {};
  }

  bool expect_element = true;

  while (!tokens.is_end()) {

    consume_statement_separators(context);

    if (tokens.match(close_token)) { return elements; }

    if (expect_element) {

      auto *element = parse_element();

      if (!element) { return {}; }

      if (element->flags.has(NodeFlags::HasError)) { return {}; }

      elements.push_back(element);

      expect_element = false;

      continue;
    }

    if (tokens.match(separator_token)) {
      expect_element = true;

      continue;
    }

    // context.//report_error(DiagnosticCode::ExpectedToken, "separator");

    return {};
  }

  // context.//report_error(DiagnosticCode::ExpectedToken, "unterminated list");

  return {};
}

} // namespace ayla::parser