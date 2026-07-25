#pragma once
#include "ast/names/QualifiedNameNode.hpp"
#include "syntax/parser/Parser.hpp"
#include "syntax/parser/ParserContext.hpp"

class NameParser {

public:
  NameParser(ParseContext &ctx, Parser &parser);

  ayla::ast::IdentifierNode *parse_name();

  ayla::ast::QualifiedNameNode *parse_qualified_name();

private:
  ParseContext &context;
  Parser &parser;
};