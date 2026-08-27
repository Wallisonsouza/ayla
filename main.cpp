#include "ayla/language/AylaLanguage.hpp"

#include "celestia/compiler/Compiler.hpp"

#include "celestia/stages/CheckStage.hpp"
#include "celestia/stages/DumperStage.hpp"
#include "celestia/stages/LanguageBootstrap.hpp"
#include "celestia/stages/LexerStage.hpp"
#include "celestia/stages/ModuleSetupStage.hpp"
#include "celestia/stages/ParserStage.hpp"
#include "celestia/stages/ResolverStage.hpp"

#include "src/CommandLine.hpp"

int main(int argc, char *argv[]) {

  auto cmd = parse_command_line(argc, argv);

  if (cmd.command != Command::Run) return 0;

  if (!cmd.input) throw std::runtime_error("Nenhum arquivo informado.");

  auto lang = ayla::language::create_definition();

  Compiler compiler(lang);

  auto bootstrap = compiler.create_frame();

  bootstrap.add_script("../src/ayla/scripts/collections.ayla")
      .add_stage<LexerStage>()
      .add_stage<ParserStage>()
      .add_stage<ModuleBootstrapSetupStage>()
      .add_stage<ResolverStage>()
      // .add_stage<LanguageBootstrapStage>()
      .add_stage<AstDumperStage>();

  bootstrap.run();

  // auto user = compiler.create_frame();
  // user
  //     .add_script(*cmd.input)
  //     .add_stage<LexerStage>()
  //     .add_stage<ParserStage>()
  //     .add_stage<ModuleSetupStage>();

  // if (has_flag(cmd.dumps, DumpFlags::Ast)) {
  //   user.add_stage<AstDumperStage>();
  // }

  // user
  //     .add_stage<ResolverStage>()
  //     .add_stage<CheckStage>();

  // user.run();
}