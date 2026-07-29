#include "context/argon_main.hpp"
#include "core/stages/CheckerStage.hpp"
#include "runtime/bytecode/Serealizer.hpp"
#include <iostream>

#include "engine/CompilationSession.hpp"

#include "core/stages/DumperStage.hpp"
#include "core/stages/LexerStage.hpp"
#include "core/stages/LoweringStage.hpp"
#include "core/stages/ParserStage.hpp"
#include "core/stages/TokenDumperStage.hpp"

#include "src/CommandLine.hpp"

int main(int argc, char *argv[]) {

  auto cmd = parse_command_line(argc, argv);

  if (cmd.command == Command::Run) {

    if (!cmd.input) throw std::runtime_error("Nenhum arquivo informado.");

    std::cout << "Arquivo: " << *cmd.input << '\n';

    auto context = ayla::language::create_context();
    CompilationSession session(context);

    session.pipeline().add_stage<LexerStage>();
    session.pipeline().add_stage<ParserStage>();
    session.pipeline().add_stage<LoweringStage>();
    session.pipeline().add_stage<ResolverStage>();

    if (has_flag(cmd.dumps, DumpFlags::Tokens)) { session.pipeline().add_stage<TokenDumperStage>(); };
    if (has_flag(cmd.dumps, DumpFlags::Ast)) { session.pipeline().add_stage<AstDumperStage>(); };

    session.add_script(*cmd.input);
    session.compile();
    session.show_diagnostics();
  }
}




