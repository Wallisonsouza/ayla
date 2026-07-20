#pragma once

#include "ast/StatementNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"

class ParseContext;
class Parser;

class StatementParser {
public:
  StatementParser(ParseContext &context, Parser &parser);

  ayla::ast::StatementNode *parse_statement();

  ayla::ast::node::BlockStatementNode *parse_block();

private:
  ayla::ast::StatementNode *parse_if();

  ayla::ast::StatementNode *parse_while();

  ayla::ast::StatementNode *parse_return();

  ayla::ast::StatementNode *parse_import();

private:
  ParseContext &context;
  Parser &parser;
};