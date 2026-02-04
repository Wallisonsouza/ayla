#include "core/node/Modifier.hpp"
#include "engine/parser/parser.hpp"

core::ast::Modifiers Parser::parse_modifiers() {
  core::ast::Modifiers mods;

  while (auto *tok = unit.tokens.peek()) {
    switch (tok->descriptor->kind) {
    case TokenKind::STATIC:
      mods.add(core::ast::Modifier::Static);
      unit.tokens.advance();
      break;
    case TokenKind::MUT:
      mods.add(core::ast::Modifier::Mut);
      unit.tokens.advance();
      break;
    case TokenKind::PUBLIC:
      mods.add(core::ast::Modifier::Public);
      unit.tokens.advance();
      break;
    case TokenKind::PRIVATE:
      mods.add(core::ast::Modifier::Private);
      unit.tokens.advance();
      break;
    case TokenKind::EXTERN_KEYWORD:
      mods.add(core::ast::Modifier::Extern);
      unit.tokens.advance();
      break;
    default: return mods;
    }
  }

  return mods;
}
