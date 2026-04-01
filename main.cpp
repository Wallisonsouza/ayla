#include "ayla-compilation/session.hpp"
#include "ayla-pipeline/lexer_pass.hpp"
#include "ayla-pipeline/parser_pass.hpp"
#include "ayla-pipeline/resolver_pass.hpp"
#include "language/argon_main.hpp"
#include <string>

int main() {

  auto context = ayla::language::create_context();

  ayla::compilation::Session session(context);

  session.add_pass(std::make_unique<LexerPass>());
  session.add_pass(std::make_unique<ParsePass>());
  session.add_pass(std::make_unique<ResolvePass>());

  session.add_unity("/home/wallison/Documentos/git/ayla/src/stdlib/io.ayla");

  session.add_unity("/home/wallison/Documentos/git/ayla/main.ayla");

  session.run_pipeline();

  return 0;
}
