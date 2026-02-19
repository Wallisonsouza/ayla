#include "engine/Session.hpp"
#include "language/argon_main.hpp"
#include "pipeline/passes/LexPass.hpp"
#include "pipeline/passes/ParsePass.hpp"
#include "pipeline/passes/ResolvePass.hpp"

int main() {

  auto context = ayla::language::create_context();

  CompilationSession session(context);

  session.add_pass(std::make_unique<LexPass>());
  session.add_pass(std::make_unique<ParsePass>());
  session.add_pass(std::make_unique<ResolvePass>());

  // session.add_pass(std::make_unique<CheckPass>());

  session.add_source("/home/wallison/Documentos/git/ayla/main.ayla");
  session.run_pipeline();

  return 0;
}