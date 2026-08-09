#pragma once
#include "celestia/ast/names/QualifiedNameNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"

namespace celestia::syntax {
class NameParser {

public:
  NameParser(ParseContext &ctx, Parser &parser);

  ast::IdentifierNode *parse_name();

  ast::QualifiedNameNode *parse_qualified_name();

private:
  ParseContext &context;
  Parser &parser;
};
} // namespace celestia::syntax