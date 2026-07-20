#include "PatternParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"
#include "TypeParser.hpp"
#include "ast/patterns/PatternNode.hpp"
#include "core/AST.hpp"
#include "core/token/token_stream.hpp"

PatternParser::PatternParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

ayla::ast::PatternNode *PatternParser::parse_pattern() {

  auto current = context.tokens().peek();

  switch (current->descriptor->kind) {
  case TokenKind::IDENTIFIER:
    return parse_identifier_pattern();

    // case TokenKind::OPEN_BRACKET:
    //     return parse_array_pattern();

    // case TokenKind::OPEN_BRACE:
    //     return parse_object_pattern();

  default: return nullptr;
  }
}

ayla::ast::PatternNode *PatternParser::parse_identifier_pattern() {

  auto *name = parser.names().parse_name();
  if (!name) return nullptr;

  ayla::ast::TypeNode *type = nullptr;

  if (context.tokens().match(TokenKind::COLON)) type = parser.types().parse_type();

  return context.ast().create_node<ayla::ast::IdentifierPatternNode>(name, type);
}
ayla::ast::PatternNode *PatternParser::parse_typed_pattern() { return nullptr; }