#include "context/argon_main.hpp"
#include "runtime/bytecode/Serealizer.hpp"
#include <memory>
#include <string>

#include "engine/CompilationSession.hpp"
#include "engine/LexerPass.hpp"

int main() {

  auto context = ayla::language::create_context();

  CompilationSession session(context);

  session.add_pass(std::make_unique<LexerPass>());
  // debug
  session.add_pass(std::make_unique<TokenDumpPass>());
  
  session.add_pass(std::make_unique<ParsePass>());
  // debug
  session.add_pass(std::make_unique<AstDumpPass>());



  auto unit = session.add_script("../scripts/main.ayla");

  session.compile();

  return 0;
}