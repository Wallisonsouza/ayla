#pragma once

namespace ayla::ast {
class TypeNode;
}

class ParseContext;
class Parser;

class TypeParser {

public:
  TypeParser(ParseContext &, Parser &);

  ayla::ast::TypeNode *parse_type();

private:
  ParseContext &context;
  Parser &parser;
};