#pragma once

#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"

namespace celestia::syntax {

class ParseContext;
class Parser;

class IdentifierExpressionNode;
class ArrayLiteralNode;

class ExpressionParser {

public:
  ExpressionParser(ParseContext &context, Parser &parser);

  ast::Expression *parse_expression();

private:
  ast::Expression *parse_assignment(ast::Expression *);

  ast::Expression *parse_binary_expression(int, ast::Expression *);

  ast::Expression *parse_unary_expression();

  ast::Expression *parse_postfix_expression();

  ast::Expression *parse_primary_expression();

  ast::Expression *parse_number_literal();

  ast::Expression *parse_string_literal();

  ast::Expression *parse_bool_literal();

  ast::Expression *parse_object_literal();

  ast::Expression *parse_grouped_expression();

  ast::Expression *parse_member_access(ast::Expression *);

  ast::Expression *parse_index_access(ast::Expression *);

  ast::Expression *parse_call(ast::Expression *);

  ast::Expression *parse_identifier_expression();

private:
  ParseContext &context;
  Parser &parser;
};
} // namespace celestia::syntax
