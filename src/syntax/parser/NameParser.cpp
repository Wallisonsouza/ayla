#include "NameParser.hpp"

NameParser::NameParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

ayla::ast::IdentifierNode *NameParser::parse_name() {
  auto &tokens = context.tokens();

  auto *token = tokens.match(TokenKind::IDENTIFIER);

  if (!token) return nullptr;

  auto text = context.source().buffer.get_text(token->slice.span);

  return context.ast().create_node<ayla::ast::IdentifierNode>(text);
}

ayla::ast::QualifiedNameNode *NameParser::parse_qualified_name() {
  auto &tokens = context.tokens();

  std::vector<ayla::ast::IdentifierNode *> parts;

  auto *first = parse_name();

  if (!first) return nullptr;

  parts.push_back(first);

  while (tokens.match(TokenKind::DOT)) {

    auto *next = parse_name();

    if (!next) return nullptr;

    parts.push_back(next);
  }

  return context.ast().create_node<ayla::ast::QualifiedNameNode>(std::move(parts));
}