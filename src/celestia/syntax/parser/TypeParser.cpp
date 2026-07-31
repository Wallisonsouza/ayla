#include "TypeParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "NameParser.hpp"

TypeParser::TypeParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

celestia::ast::TypeNode *TypeParser::parse_type() {
  auto *name = parser.names().parse_name();

  if (!name) return nullptr;

  std::vector<celestia::ast::TypeNode *> generic_arguments;

  // futuramente:
  // if (tokens.match(TokenKind::LESS))
  //     generic_arguments = parse_generic_arguments();

  return context.get_ast().create_node<celestia::ast::TypeNode>(name, std::move(generic_arguments));
}