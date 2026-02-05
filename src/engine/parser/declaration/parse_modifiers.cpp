#include "core/node/Modifier.hpp"
#include "engine/parser/parser.hpp"

ayla::ast::Modifiers Parser::parse_modifiers() {
  ayla::ast::Modifiers mods;

  while (auto *tok = unit.tokens.peek()) {
    switch (tok->descriptor->kind) {
    case TokenKind::STATIC:
      mods.add(ayla::ast::Modifier::Static);
      unit.tokens.advance();
      break;
    case TokenKind::MUT:
      mods.add(ayla::ast::Modifier::Mut);
      unit.tokens.advance();
      break;
    case TokenKind::PUBLIC:
      mods.add(ayla::ast::Modifier::Public);
      unit.tokens.advance();
      break;
    case TokenKind::PRIVATE:
      mods.add(ayla::ast::Modifier::Private);
      unit.tokens.advance();
      break;
    case TokenKind::EXTERN_KEYWORD:
      mods.add(ayla::ast::Modifier::Extern);
      unit.tokens.advance();
      break;
    default: return mods;
    }
  }

  return mods;
}
