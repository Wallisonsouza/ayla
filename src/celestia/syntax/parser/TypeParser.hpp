#pragma once

#include "celestia/ast/types/FunctionType.hpp"
#include "celestia/ast/types/ReferenceType.hpp"
#include "celestia/ast/types/TypeNode.hpp"
#include "celestia/syntax/parser/ParseStatus.hpp"
#include "celestia/syntax/parser/Parser.hpp"

namespace celestia::syntax {
class ParseContext;
class Parser;

class TypeParser {

public:
  TypeParser(ParseContext &, Parser &);

  ParseResult<ast::TypeNode *> parse_type();

  ParseResult<ast::TypeNode *> parse_named_type();

  ParseResult<ast::TypeNode *> parse_array_type();

  ParseResult<ast::TypeNode *> parse_reference_type();

  ParseResult<ast::TypeNode *> parse_function_type();

private:
  ParseContext &context;
  Parser &parser;
};
} // namespace celestia::syntax
