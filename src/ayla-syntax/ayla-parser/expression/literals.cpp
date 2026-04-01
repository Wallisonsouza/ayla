#include "ayla-syntax/ayla-parser/parser.hpp"

core::ast::ASTExpressionNode *Parser::parse_number_literal() {
  Token *token = unit.tokens.match(TokenKind::NUMBER_LITERAL);
  if (!token) return nullptr;

  std::string text = unit.source.buffer.get_text(token->slice.span);
  try {
    double value = std::stod(text);
    return unit.ast.create_node<parser::node::NumberLiteralNode>(value);
  } catch (const std::exception &) { return nullptr; }
}

core::ast::ASTExpressionNode *Parser::parse_string_literal() {

  Token *token = unit.tokens.match(TokenKind::STRING_LITERAL);
  if (!token) return nullptr;

  std::string text = unit.source.buffer.get_text(token->slice.span);

  return unit.ast.create_node<parser::node::StringLiteralNode>(text);
}

core::ast::IdentifierNode *Parser::parse_identifier() {

  Token *token = unit.tokens.match(TokenKind::IDENTIFIER);
  if (!token) return nullptr;

  auto *node = unit.ast.create_node<core::ast::IdentifierNode>(unit.source.buffer.get_text(token->slice.span));
  node->slice = token->slice;

  return node;
}

core::ast::ASTExpressionNode *Parser::parse_object_literal() {

  auto *fieldList =
      parse_generic_list<parser::node::ASTObjectFieldList, parser::node::ObjectFieldNode>(TokenKind::OPEN_BRACE, TokenKind::CLOSE_BRACE, TokenKind::COMMA, [&]() -> parser::node::ObjectFieldNode * {
        auto *key = parse_identifier();
        if (!key) return nullptr;

        unit.tokens.expect(TokenKind::COLON);

        auto *value = parse_expression();
        if (!value) return nullptr;

        return unit.ast.create_node<parser::node::ObjectFieldNode>(key, value);
      });

  if (!fieldList) return nullptr;

  return unit.ast.create_node<parser::node::ObjectLiteralNode>(fieldList);
}