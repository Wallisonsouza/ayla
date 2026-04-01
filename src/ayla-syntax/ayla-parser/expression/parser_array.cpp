#include "ayla-syntax/ayla-parser/parser.hpp"

parser::node::ASTArrayLiteralNode *Parser::parse_array_literal() {
  return parse_generic_list<parser::node::ASTArrayLiteralNode, core::ast::ASTExpressionNode>(TokenKind::OPEN_BRACKET, TokenKind::CLOSE_BRACKET, TokenKind::COMMA, [&]() { return parse_expression(); });
}