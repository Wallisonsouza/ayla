#include "NameParser.hpp"
#include "celestia/core/token/TokenKind.hpp"
#include "celestia/syntax/parser/ParserContext.hpp"

namespace celestia::syntax {
NameParser::NameParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

celestia::ast::IdentifierNode *NameParser::parse_name() {
  auto &tokens = context.tokens();

  auto *token = tokens.match(TokenKind::IDENTIFIER);

  if (!token) return nullptr;

  auto text = context.source().buffer.get_text(token->slice.get_span());

  return context.get_ast().create_node<celestia::ast::IdentifierNode>(text);
}

celestia::ast::QualifiedNameNode *NameParser::parse_qualified_name() {
  auto &tokens = context.tokens();

  std::vector<celestia::ast::IdentifierNode *> parts;

  auto *first = parse_name();

  if (!first) return nullptr;

  parts.push_back(first);

  while (tokens.match(TokenKind::DOT)) {

    auto *next = parse_name();

    if (!next) return nullptr;

    parts.push_back(next);
  }

  return context.get_ast().create_node<celestia::ast::QualifiedNameNode>(std::move(parts));
}
} // namespace celestia::syntax