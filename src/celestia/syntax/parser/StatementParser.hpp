#pragma once

#include "celestia/ast/StatementNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"

class ParseContext;
class Parser;

class StatementParser {
public:
  StatementParser(ParseContext &context, Parser &parser);

  celestia::ast::StatementNode *parse_statement();

  celestia::ast::node::BlockStatementNode *parse_block_statement();

private:
  celestia::ast::StatementNode *parse_if_statement();

  celestia::ast::StatementNode *parse_while_statement();

  celestia::ast::StatementNode *parse_return_statement();
  
  celestia::ast::StatementNode *parse_expression_statement();

private:
  ParseContext &context;
  Parser &parser;
};