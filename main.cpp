#include "context/argon_main.hpp"
#include "debug/engine/token/dump_tokens.hpp"
#include "runtime/bytecode/Serealizer.hpp"
#include <iostream>
#include <memory>
#include <string>

#include "engine/CompilationSession.hpp"
#include "engine/LexerPass.hpp"

int main() {

  auto context = ayla::language::create_context();

  CompilationSession session(context);

  session.add_pass(std::make_unique<LexerPass>());
  session.add_pass(std::make_unique<ParsePass>());
  // session.add_pass(std::make_unique<ResolvePass>());
  // session.add_pass(std::make_unique<CheckPass>());

  session.add_pass(std::make_unique<AstDebug>());

  auto unit = session.add_script("../scripts/main.ayla");

  session.compile();


  //  debug::engine::dump_tokens(unit->tokens);

  return 0;
}