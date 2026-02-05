#include "engine/parser/parser.hpp"

ayla::ast::node::ASTArrayLiteralNode *Parser::parse_array_literal() {

  auto elements = parse_generic_list<ayla::ast::ExpressionNode>(TokenKind::OPEN_BRACKET, TokenKind::CLOSE_BRACKET, TokenKind::COMMA, [&]() { return parse_expression(); });

  return unit.ast.create_node<ayla::ast::node::ASTArrayLiteralNode>(std::move(elements));
}