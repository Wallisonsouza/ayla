#pragma once


#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"

class ParseContext;
class Parser;

namespace celestia::ast {
class IdentifierExpressionNode;
class ArrayLiteralNode;
} // namespace celestia::ast

class ExpressionParser {

public:
  ExpressionParser(ParseContext &context, celestia::Parser &parser);

  celestia::ast::Expression *parse_expression();

private:
  celestia::ast::Expression *parse_assignment(celestia::ast::Expression *);

  celestia::ast::Expression *parse_binary_expression(int, celestia::ast::Expression *);

  celestia::ast::Expression *parse_unary_expression();

  celestia::ast::Expression *parse_postfix_expression();

  celestia::ast::Expression *parse_primary_expression();

  celestia::ast::Expression *parse_number_literal();

  celestia::ast::Expression *parse_string_literal();

  celestia::ast::Expression *parse_bool_literal();

  celestia::ast::Expression *parse_object_literal();

  celestia::ast::Expression *parse_grouped_expression();

  celestia::ast::Expression *parse_member_access(celestia::ast::Expression *);

  celestia::ast::Expression *parse_index_access(celestia::ast::Expression *);

  celestia::ast::Expression *parse_call(celestia::ast::Expression *);

  celestia::ast::Expression *parse_identifier_expression();

private:
  ParseContext &context;
  celestia::Parser &parser;
};