#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/parser/parser.hpp"

core::ast::ASTStatementNode *Parser::parse_statement() {

  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  switch (tok->descriptor->kind) {

  case TokenKind::IMPORT_KEYWORD: return parse_import_statement();

  case TokenKind::IF_KEYWORD: return parse_if_statement();

  case TokenKind::WHILE_KEYWORD: return parse_while_statemente();

  case TokenKind::RETURN_KEYWORD: return parse_return_statement();

  case TokenKind::VALUE_KEYWORD:
  case TokenKind::CONST_KEYWORD: return parse_variable_declaration();

  case TokenKind::FUNCTION_KEYWORD: return parse_function_declaration();

  default:
    if (auto *expr = parse_expression()) { return unit.ast.create_node<core::ast::ExpressionStatementNode>(expr); }

    unit.tokens.advance();
    return nullptr;
  }
}