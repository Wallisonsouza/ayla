#pragma once


#include "celestia/ast/ExpressionNode.hpp"

class ParseContext;
class Parser;

namespace celestia::ast::node {
class IdentifierExpressionNode;
class ArrayLiteralNode;
} // namespace celestia::ast::node

class ExpressionParser {

public:
  ExpressionParser(ParseContext &context, Parser &parser);

  celestia::ast::ExpressionNode *parse_expression();

private:
  celestia::ast::ExpressionNode *parse_assignment(celestia::ast::ExpressionNode *);

  celestia::ast::ExpressionNode *parse_binary_expression(int, celestia::ast::ExpressionNode *);

  celestia::ast::ExpressionNode *parse_unary_expression();

  celestia::ast::ExpressionNode *parse_postfix_expression();

  celestia::ast::ExpressionNode *parse_primary_expression();

  celestia::ast::ExpressionNode *parse_number_literal();

  celestia::ast::ExpressionNode *parse_string_literal();

  celestia::ast::ExpressionNode *parse_bool_literal();

  celestia::ast::ExpressionNode *parse_object_literal();

  celestia::ast::ExpressionNode *parse_grouped_expression();

  celestia::ast::ExpressionNode *parse_member_access(celestia::ast::ExpressionNode *);

  celestia::ast::ExpressionNode *parse_index_access(celestia::ast::ExpressionNode *);

  celestia::ast::ExpressionNode *parse_call(celestia::ast::ExpressionNode *);

  celestia::ast::ExpressionNode *parse_identifier_expression();

private:
  ParseContext &context;
  Parser &parser;
};