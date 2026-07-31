#pragma once

namespace celestia::ast {
class TypeNode;
}

class ParseContext;
class Parser;

class TypeParser {

public:
  TypeParser(ParseContext &, Parser &);

  celestia::ast::TypeNode *parse_type();

private:
  ParseContext &context;
  Parser &parser;
};