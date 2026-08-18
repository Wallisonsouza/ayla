#include "TypeParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"
#include "celestia/ast/types/Array.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/ast/types/ReferenceType.hpp"
#include <iostream>

namespace celestia::syntax {
TypeParser::TypeParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

celestia::ast::TypeNode *TypeParser::parse_type() {

  auto &tokens = context.tokens();

  switch (tokens.peek()->kind()) {

  case TokenKind::REF_KEYWORD: return parse_reference_type();

  case TokenKind::OPEN_BRACKET: return parse_array_type();

  case TokenKind::IDENTIFIER: return parse_named_type();

  default: return nullptr;
  }
}

celestia::ast::TypeNode *TypeParser::parse_named_type() {

  auto *name = parser.names().parse_name();

  if (!name) return nullptr;

  return context.get_ast().create_node<celestia::ast::NamedType>(name);
}

celestia::ast::TypeNode *TypeParser::parse_array_type() {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::OPEN_BRACKET)) return nullptr;

  auto *element_type = parse_type();

  if (!element_type) return nullptr;

  if (!tokens.match(TokenKind::CLOSE_BRACKET)) return nullptr;

  return context.get_ast().create_node<celestia::ast::ArrayType>(element_type);
}

celestia::ast::TypeNode *TypeParser::parse_reference_type() {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::REF_KEYWORD)) return nullptr;

  if (!tokens.match(TokenKind::LESS)) return nullptr;



  auto *target = parse_type();

  if (!target) return nullptr;

  if (!tokens.match(TokenKind::GREATER)) return nullptr;
 
  return context.get_ast().create_node<celestia::ast::ReferenceType>(target);
}

} // namespace celestia::syntax
