#include "PatternParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"
#include "TypeParser.hpp"
#include "celestia/ast/patterns/IdentifierPatternNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/core/AST.hpp"
#include "celestia/core/token/token_stream.hpp"

namespace celestia::syntax {
PatternParser::PatternParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

ast::PatternNode *PatternParser::parse_pattern() {

  auto current = context.tokens().peek();

  switch (current->desc->kind) {
  case TokenKind::IDENTIFIER:
    return parse_identifier_pattern();

    // case TokenKind::OPEN_BRACKET:
    //     return parse_array_pattern();

    // case TokenKind::OPEN_BRACE:
    //     return parse_object_pattern();

  default: return nullptr;
  }
}

ast::PatternNode *PatternParser::parse_identifier_pattern() {

  auto *name = parser.names().parse_name();
  if (!name) return nullptr;

  ast::TypeNode *type = nullptr;

  if (context.tokens().match(TokenKind::COLON)) type = parser.types().parse_type();

  return context.get_ast().create_node<ast::IdentifierPatternNode>(name, type);
}
ast::PatternNode *PatternParser::parse_typed_pattern() { return nullptr; }
} // namespace celestia::syntax
