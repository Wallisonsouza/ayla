#pragma once

#include "celestia/syntax/parser/ParseStatus.hpp"

namespace celestia::ast {
class PatternNode;
}

namespace celestia::syntax {

class ParseContext;
class Parser;

class PatternParser {
public:
  PatternParser(ParseContext &context, Parser &parser);

  ParseResult<ast::PatternNode *> parse_pattern();
  ParseResult<ast::PatternNode *> parse_identifier_pattern();
  ParseResult<ast::PatternNode *> parse_typed_pattern();

private:
  ParseContext &context;
  Parser &parser;
};

} // namespace celestia::syntax