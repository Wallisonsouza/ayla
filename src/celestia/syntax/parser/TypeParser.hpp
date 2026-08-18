#pragma once

#include "celestia/ast/types/TypeNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"

namespace celestia::syntax {
class ParseContext;
class Parser;

class TypeParser {

public:
  TypeParser(ParseContext &, Parser &);

  ast::TypeNode *parse_type();
  celestia::ast::TypeNode *parse_array_type();
  celestia::ast::TypeNode *parse_named_type();
  celestia::ast::TypeNode *parse_reference_type();

private:
  ParseContext &context;
  Parser &parser;
};
} // namespace celestia::syntax
