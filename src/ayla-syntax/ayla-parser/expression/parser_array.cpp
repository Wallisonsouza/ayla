#include "ayla-syntax/ayla-parser/parser.hpp"

parser::node::ASTArrayLiteralNode *Parser::parse_array_literal() {
  return parse_generic_list<parser::node::ASTArrayLiteralNode, core::ast::ASTExpressionNode>(ayla::structural::token::TokenKind::OPEN_BRACKET, ayla::structural::token::TokenKind::CLOSE_BRACKET,
                                                                                             ayla::structural::token::TokenKind::COMMA, [&]() { return parse_expression(); });
}