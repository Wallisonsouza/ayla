#pragma once

#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"

namespace celestia::syntax {

class Parser;

class ParseContext;
class PatternParser {
public:
  PatternParser(ParseContext &, Parser &);

  ast::PatternNode *parse_pattern();

private:
  ast::PatternNode *parse_identifier_pattern();

  ast::PatternNode *parse_typed_pattern();

private:
  ParseContext &context;
  Parser &parser;
};
} // namespace celestia::syntax