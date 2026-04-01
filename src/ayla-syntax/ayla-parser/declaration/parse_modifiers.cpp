#include "ayla-syntax/ayla-parser/parser.hpp"
#include "core/node/Modifier.hpp"

core::ast::Modifiers Parser::parse_modifiers() {
  core::ast::Modifiers mods;

  while (auto *tok = unit.tokens.peek()) {
    switch (tok->descriptor->kind) {
    case ayla::structural::token::TokenKind::STATIC:
      mods.add(core::ast::Modifier::Static);
      unit.tokens.advance();
      break;
    case ayla::structural::token::TokenKind::MUT:
      mods.add(core::ast::Modifier::Mut);
      unit.tokens.advance();
      break;
    case ayla::structural::token::TokenKind::PUBLIC:
      mods.add(core::ast::Modifier::Public);
      unit.tokens.advance();
      break;
    case ayla::structural::token::TokenKind::PRIVATE:
      mods.add(core::ast::Modifier::Private);
      unit.tokens.advance();
      break;
    case ayla::structural::token::TokenKind::EXTERN_KEYWORD:
      mods.add(core::ast::Modifier::Extern);
      unit.tokens.advance();
      break;
    default: return mods;
    }
  }

  return mods;
}
