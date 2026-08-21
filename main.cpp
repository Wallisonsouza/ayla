#include "ayla/language/AylaLanguage.hpp"

#include <iostream>

#include "celestia/compiler/Compiler.hpp"

#include "celestia/stages/ResolverStage.hpp"
#include "celestia/stages/DumperStage.hpp"
#include "celestia/stages/LexerStage.hpp"
#include "celestia/stages/LoweringStage.hpp"
#include "celestia/stages/ParserStage.hpp"
#include "celestia/stages/TokenDumperStage.hpp"
#include "celestia/stages/Transpiler.hpp"

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

    compiler.pipeline.add_stage<CTranspilePass>();

    compiler.add_script(*cmd.input);
    compiler.compile();

    // session.show_diagnostics();
  }
}
