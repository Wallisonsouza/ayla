#pragma once

#include "celestia/ast/TypeNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"

namespace celestia::syntax {
class ParseContext;
class Parser;

class TypeParser {

public:
  TypeParser(ParseContext &, Parser &);

  ast::TypeNode *parse_type();

private:
  ParseContext &context;
  Parser &parser;
};
} // namespace celestia::syntax
