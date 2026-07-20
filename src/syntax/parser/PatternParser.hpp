#pragma once

#include "ast/patterns/PatternNode.hpp"

class ParseContext;
class Parser;

class PatternParser {
public:
  PatternParser(ParseContext &, Parser &);

  ayla::ast::PatternNode *parse_pattern();

private:
  ayla::ast::PatternNode *parse_identifier_pattern();

  ayla::ast::PatternNode *parse_typed_pattern();

private:
  ParseContext &context;
  Parser &parser;
};