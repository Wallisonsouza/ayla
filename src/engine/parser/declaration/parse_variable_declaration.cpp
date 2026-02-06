#include "engine/parser/parser.hpp"

ayla::ast::node::VariableDeclarationNode *Parser::parse_variable_declaration(ayla::ast::Modifiers modifiers) {

  bool is_const = unit.tokens.match(TokenKind::CONST_KEYWORD);

  if (!is_const) {
    if (!unit.tokens.match(TokenKind::VALUE_KEYWORD)) return nullptr;
  }

  // pattern
  auto *pattern = parse_pattern();
  if (!pattern) return nullptr;

  // initializer opcional
  ayla::ast::ExpressionNode *init = nullptr;

  if (unit.tokens.match(TokenKind::ASSIGN)) { init = parse_expression(); }

  return unit.ast.create_node<ayla::ast::node::VariableDeclarationNode>(pattern, init, modifiers);
}
