#pragma once

#include "celestia/ast/patterns/PatternNode.hpp"

class ParseContext;
class Parser;

class PatternParser {
public:
  PatternParser(ParseContext &, Parser &);

  celestia::ast::PatternNode *parse_pattern();

private:
  celestia::ast::PatternNode *parse_identifier_pattern();

  celestia::ast::PatternNode *parse_typed_pattern();

private:
  ParseContext &context;
  Parser &parser;
};