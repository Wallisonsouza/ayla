#pragma once

#include "celestia/ast/statements/StatementNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"

class ParseContext;
class Parser;

class StatementParser {
public:
  StatementParser(ParseContext &context, celestia::Parser &parser);

  celestia::ast::Statement *parse_statement();

  celestia::ast::BlockStatement *parse_block_statement();

private:
  celestia::ast::Statement *parse_if_statement();

  celestia::ast::Statement *parse_while_statement();

  celestia::ast::Statement *parse_return_statement();
  
  celestia::ast::Statement *parse_expression_statement();

private:
  ParseContext &context;
  celestia::Parser &parser;
};