#include "ayla/language/AylaLanguage.hpp"
#include "celestia/core/stages/ResolverStage.hpp"
#include <iostream>

#include "celestia/engine/CompilationSession.hpp"

#include "celestia/core/stages/DumperStage.hpp"
#include "celestia/core/stages/LexerStage.hpp"
#include "celestia/core/stages/LoweringStage.hpp"
#include "celestia/core/stages/ParserStage.hpp"
#include "celestia/core/stages/TokenDumperStage.hpp"

#include "src/CommandLine.hpp"

int main(int argc, char *argv[]) {

  auto cmd = parse_command_line(argc, argv);

  if (cmd.command == Command::Run) {

    if (!cmd.input) throw std::runtime_error("Nenhum arquivo informado.");

    std::cout << "Arquivo: " << *cmd.input << '\n';

    auto lang = ayla::language::create_definition();

    CompilationSession session;

    session.environment().language = lang;

    session.pipeline.add_stage<LexerStage>();
    session.pipeline.add_stage<ParserStage>();
    session.pipeline.add_stage<LoweringStage>();
    session.pipeline.add_stage<ResolverStage>();

    if (has_flag(cmd.dumps, DumpFlags::Tokens)) { session.pipeline.add_stage<TokenDumperStage>(); };
    if (has_flag(cmd.dumps, DumpFlags::Ast)) { session.pipeline.add_stage<AstDumperStage>(); };

    session.add_script(*cmd.input);
    session.compile();

    session.diagnostics();
    // session.show_diagnostics();
  }
}
