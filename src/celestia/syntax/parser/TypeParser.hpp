#pragma once


#include "celestia/ast/TypeNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"
class ParseContext;
class Parser;

class TypeParser {

public:
  TypeParser(ParseContext &, celestia::Parser &);

  celestia::ast::TypeNode *parse_type();

private:
  ParseContext &context;
  celestia::Parser &parser;
};