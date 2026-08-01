#pragma once
#include "celestia/ast/names/QualifiedNameNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"
#include "celestia/syntax/parser/ParserContext.hpp"

class NameParser {

public:
  NameParser(ParseContext &ctx, celestia::Parser &parser);

 celestia::ast::IdentifierNode *parse_name();

 celestia::ast::QualifiedNameNode *parse_qualified_name();

private:
  ParseContext &context;
  celestia::Parser &parser;
};