#include "engine/parser/parser.hpp"
#include "frontend/ast/expressions/CallExpressionNode.hpp"

ayla::ast::ExpressionNode *Parser::parse_member_acess(ayla::ast::ExpressionNode *base) {

  auto *dot = unit.tokens.match(TokenKind::DOT);
  if (!dot) return nullptr;

  auto *field = parse_identifier();

  if (!field) { return nullptr; }

  return unit.ast.create_node<parser::node::MemberAccessNode>(base, field);
}

ayla::ast::ExpressionNode *Parser::parse_index_access(ayla::ast::ExpressionNode *base) {

  auto *open = unit.tokens.match(TokenKind::OPEN_BRACKET);
  if (!open) return nullptr; // erro: '[' esperado

  ayla::ast::ExpressionNode *index_expr = parse_expression();
  if (!index_expr) return nullptr; // erro: expressão esperada dentro de '[]'

  auto *close = unit.tokens.match(TokenKind::CLOSE_BRACKET);
  if (!close) return nullptr; // erro: ']' esperado

  return unit.ast.create_node<parser::node::IndexAccessNode>(base, index_expr);
}

ayla::ast::ExpressionNode *Parser::parse_call_acess(ayla::ast::ExpressionNode *base) {
  if (!base) return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok || tok->descriptor->kind != TokenKind::OPEN_PAREN) break;
    unit.tokens.advance(); // consumir '('

    std::vector<ayla::ast::ExpressionNode *> args;
    while (!unit.tokens.is_end() && !unit.tokens.match(TokenKind::CLOSE_PAREN)) {
      auto *expr = parse_expression();
      if (!expr) break;
      args.push_back(expr);

      if (!unit.tokens.match(TokenKind::COMMA)) {
        unit.tokens.match(TokenKind::CLOSE_PAREN);
        break;
      }
    }

    base = unit.ast.create_node<ayla::ast::node::CallExpressionNode>(base, args);
  }

  return base;
}