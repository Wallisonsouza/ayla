#include "context/argon_main.hpp"
#include "runtime/bytecode/Serealizer.hpp"
#include <string>

#include "engine/CompilationSession.hpp"

#include "core/stages/DumperStage.hpp"
#include "core/stages/LexerStage.hpp"
#include "core/stages/LoweringStage.hpp"
#include "core/stages/ParserStage.hpp"
int main() {

  auto context = ayla::language::create_context();

  CompilationSession session(context);

  session.pipeline().add_stage<LexerStage>();
  session.pipeline().add_stage<ParserStage>();
  session.pipeline().add_stage<LoweringStage>();


  session.pipeline().add_stage<DumperStage>();
 

  session.add_script("../scripts/teste.ayla");

  session.compile();


  return 0;
}