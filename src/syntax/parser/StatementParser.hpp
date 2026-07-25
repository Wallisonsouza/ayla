#pragma once

#include "ast/StatementNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"

class ParseContext;
class Parser;

class StatementParser {
public:
  StatementParser(ParseContext &context, Parser &parser);

  ayla::ast::StatementNode *parse_statement();

  ayla::ast::node::BlockStatementNode *parse_block_statement();

private:
  ayla::ast::StatementNode *parse_if_statement();

  ayla::ast::StatementNode *parse_while_statement();

  ayla::ast::StatementNode *parse_return_statement();


private:
  ParseContext &context;
  Parser &parser;
};