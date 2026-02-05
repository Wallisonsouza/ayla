#include "engine/parser/parser.hpp"

parser::node::ASTArrayLiteralNode *Parser::parse_array_literal() {
  return parse_generic_list<parser::node::ASTArrayLiteralNode, ayla::ast::ExpressionNode>(TokenKind::OPEN_BRACKET, TokenKind::CLOSE_BRACKET, TokenKind::COMMA, [&]() { return parse_expression(); });
}