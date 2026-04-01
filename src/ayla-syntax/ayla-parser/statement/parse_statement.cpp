#include "ayla-syntax/ayla-parser/parser.hpp"
#include "core/node/Type.hpp"

core::ast::ASTStatementNode *Parser::parse_statement() {
  auto modifiers = parse_modifiers();
  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  switch (tok->descriptor->kind) {
  case ayla::structural::token::TokenKind::MODULE_KEYWORD: return parse_module_declaration();
  case ayla::structural::token::TokenKind::IMPORT_KEYWORD: return parse_import_statement();
  case ayla::structural::token::TokenKind::IF_KEYWORD: return parse_if_statement();
  case ayla::structural::token::TokenKind::WHILE_KEYWORD: return parse_while_statemente();
  case ayla::structural::token::TokenKind::RETURN_KEYWORD: return parse_return_statement();
  case ayla::structural::token::TokenKind::VALUE_KEYWORD:
  case ayla::structural::token::TokenKind::CONST_KEYWORD: return parse_variable_declaration(modifiers);
  case ayla::structural::token::TokenKind::FUNCTION_KEYWORD: return parse_function_declaration(modifiers);
  default:
    if (auto *expr = parse_expression()) { return unit.ast.create_node<core::ast::ExpressionStatementNode>(expr); }
    unit.tokens.advance();
    return nullptr;
  }
}
