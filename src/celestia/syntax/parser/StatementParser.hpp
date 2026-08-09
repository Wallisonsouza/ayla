#pragma once

#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/statements/StatementNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"

namespace celestia::syntax {
class ParseContext;
class Parser;

class StatementParser {
public:
  StatementParser(ParseContext &context, Parser &parser);

  ast::Statement *parse_statement();

  ast::BlockStatement *parse_block_statement();

private:
  ast::Statement *parse_if_statement();

  ast::Statement *parse_while_statement();

  ast::Statement *parse_return_statement();

  ast::Statement *parse_expression_statement();

private:
  ParseContext &context;
  Parser &parser;
};
} // namespace celestia::syntax