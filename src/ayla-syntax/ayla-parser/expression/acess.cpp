#include "ayla-syntax/ayla-parser/parser.hpp"

core::ast::ASTExpressionNode *Parser::parse_member_acess(core::ast::ASTExpressionNode *base) {

  auto *dot = unit.tokens.match(ayla::structural::token::TokenKind::DOT);
  if (!dot) return nullptr;

  auto *field = parse_identifier();

  if (!field) { return nullptr; }

  return unit.ast.create_node<parser::node::MemberAccessNode>(base, field);
}

core::ast::ASTExpressionNode *Parser::parse_index_access(core::ast::ASTExpressionNode *base) {

  auto *open = unit.tokens.match(ayla::structural::token::TokenKind::OPEN_BRACKET);
  if (!open) return nullptr; // erro: '[' esperado

  core::ast::ASTExpressionNode *index_expr = parse_expression();
  if (!index_expr) return nullptr; // erro: expressão esperada dentro de '[]'

  auto *close = unit.tokens.match(ayla::structural::token::TokenKind::CLOSE_BRACKET);
  if (!close) return nullptr; // erro: ']' esperado

  return unit.ast.create_node<parser::node::IndexAccessNode>(base, index_expr);
}

core::ast::ASTExpressionNode *Parser::parse_call_acess(core::ast::ASTExpressionNode *base) {
  if (!base) return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok || tok->descriptor->kind != ayla::structural::token::TokenKind::OPEN_PAREN) break;
    unit.tokens.advance(); // consumir '('

    std::vector<core::ast::ASTExpressionNode *> args;
    while (!unit.tokens.is_end() && !unit.tokens.match(ayla::structural::token::TokenKind::CLOSE_PAREN)) {
      auto *expr = parse_expression();
      if (!expr) break;
      args.push_back(expr);

      if (!unit.tokens.match(ayla::structural::token::TokenKind::COMMA)) {
        unit.tokens.match(ayla::structural::token::TokenKind::CLOSE_PAREN);
        break;
      }
    }

    base = unit.ast.create_node<parser::node::FunctionCallNode>(base, args);
  }

  return base;
}