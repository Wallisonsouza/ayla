#include "ayla/language/AylaLanguage.hpp"
#include "celestia/core/stages/ResolverStage.hpp"
#include <iostream>

#include "celestia/engine/Compiler.hpp"

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

    Compiler compiler(lang);

    compiler.pipeline.add_stage<LexerStage>();
    compiler.pipeline.add_stage<ParserStage>();
    compiler.pipeline.add_stage<LoweringStage>();
    compiler.pipeline.add_stage<ResolverStage>();

    if (has_flag(cmd.dumps, DumpFlags::Tokens)) { compiler.pipeline.add_stage<TokenDumperStage>(); };
    if (has_flag(cmd.dumps, DumpFlags::Ast)) { compiler.pipeline.add_stage<AstDumperStage>(); };

    compiler.add_script(*cmd.input);
    compiler.compile();

    compiler.diagnostics();
    // session.show_diagnostics();
  }
}
