#include "engine/parser/parser.hpp"
#include "frontend/ast/expressions/LiteralExpressionNode.hpp"

ayla::ast::ExpressionNode *Parser::parse_number_literal() {
  Token *token = unit.tokens.match(TokenKind::NUMBER_LITERAL);
  if (!token) return nullptr;

  std::string text = unit.source.buffer.get_text(token->slice.span);
  try {
    double value = std::stod(text);
    return unit.ast.create_node<ayla::ast::node::NumberLiteralNode>(value);
  } catch (const std::exception &) { return nullptr; }
}

ayla::ast::ExpressionNode *Parser::parse_string_literal() {

  Token *token = unit.tokens.match(TokenKind::STRING_LITERAL);
  if (!token) return nullptr;

  std::string text = unit.source.buffer.get_text(token->slice.span);

  return unit.ast.create_node<ayla::ast::node::StringLiteralNode>(text);
}

ayla::ast::ExpressionNode *Parser::parse_bool_literal() {

  Token *token = unit.tokens.advance();
  if (!token) return nullptr;

  bool value = (token->descriptor->kind == TokenKind::TRUE_KEYWORD);

  auto *node = unit.ast.create_node<ayla::ast::node::BoolLiteralNode>(value);
  node->slice = token->slice;

  return node;
}

ayla::ast::ExpressionNode *Parser::parse_object_literal() {

  auto fields = parse_generic_list<ayla::ast::node::ObjectFieldNode>(TokenKind::OPEN_BRACE, TokenKind::CLOSE_BRACE, TokenKind::COMMA, [&]() -> ayla::ast::node::ObjectFieldNode * {
    auto *key = parse_identifier();
    if (!key) return nullptr;

    unit.tokens.expect(TokenKind::COLON);

    auto *value = parse_expression();
    if (!value) return nullptr;

    return unit.ast.create_node<ayla::ast::node::ObjectFieldNode>(key, value);
  });

  if (fields.empty()) return nullptr;

  return unit.ast.create_node<ayla::ast::node::ObjectLiteralNode>(std::move(fields));
}
