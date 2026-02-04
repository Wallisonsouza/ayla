#include "engine/parser/parser.hpp"

core::ast::ASTExpressionNode *Parser::parse_postfix_expression() {

  auto *expr = parse_primary_expression();
  if (!expr) return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok) break;

    switch (tok->descriptor->kind) {

    case TokenKind::OPEN_PAREN:
      expr = parse_call_acess(expr);
      if (!expr) return nullptr;
      break;

    case TokenKind::DOT:
      expr = parse_member_acess(expr);
      if (!expr) return nullptr;
      break;

    case TokenKind::OPEN_BRACKET:
      expr = parse_index_access(expr);
      if (!expr) return nullptr;
      break;

    default: return expr;
    }
  }

  return expr;
}
