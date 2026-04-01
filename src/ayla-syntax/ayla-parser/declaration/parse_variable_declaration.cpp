#include "ayla-syntax/ayla-parser/parser.hpp"
#include "core/node/flags.hpp"

core::ast::ASTStatementNode *Parser::parse_variable_declaration(core::ast::Modifiers modifiers) {
  auto mods = parse_modifiers();

  if (!unit.tokens.match(TokenKind::VALUE_KEYWORD) && !unit.tokens.match(TokenKind::CONST_KEYWORD)) { return nullptr; }

  auto *pattern = parse_pattern(mods);

  if (pattern->flags.has(NodeFlags::HasError)) { recover_until(RecoverBoundary::Variable); }

  return pattern;
}
