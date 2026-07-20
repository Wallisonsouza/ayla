#pragma once

#include "ast/ExpressionNode.hpp"

class ParseContext;
class Parser;

namespace ayla::ast::node {
class IdentifierExpressionNode;
class ArrayLiteralNode;
} // namespace ayla::ast::node

class ExpressionParser {

public:
  ExpressionParser(ParseContext &context, Parser &parser);

  ayla::ast::ExpressionNode *parse_expression();

private:
  ayla::ast::ExpressionNode *parse_assignment(ayla::ast::ExpressionNode *);

  ayla::ast::ExpressionNode *parse_binary_expression(int, ayla::ast::ExpressionNode *);

  ayla::ast::ExpressionNode *parse_unary_expression();

  ayla::ast::ExpressionNode *parse_postfix_expression();

  ayla::ast::ExpressionNode *parse_primary_expression();

  ayla::ast::ExpressionNode *parse_number_literal();

  ayla::ast::ExpressionNode *parse_string_literal();

  ayla::ast::ExpressionNode *parse_bool_literal();

  ayla::ast::ExpressionNode *parse_object_literal();

  ayla::ast::ExpressionNode *parse_grouped_expression();

  ayla::ast::ExpressionNode *parse_member_access(ayla::ast::ExpressionNode *);

  ayla::ast::ExpressionNode *parse_index_access(ayla::ast::ExpressionNode *);

  ayla::ast::ExpressionNode *parse_call(ayla::ast::ExpressionNode *);

  ayla::ast::ExpressionNode *parse_identifier_expression();

private:
  ParseContext &context;
  Parser &parser;
};