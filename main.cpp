#include "ayla/language/AylaLanguage.hpp"

#include "celestia/compiler/Compiler.hpp"

#include "celestia/stages/CheckStage.hpp"
#include "celestia/stages/DumperStage.hpp"
#include "celestia/stages/LanguageBootstrap.hpp"
#include "celestia/stages/LexerStage.hpp"
#include "celestia/stages/LoweringStage.hpp"
#include "celestia/stages/ModuleSetupStage.hpp"
#include "celestia/stages/ParserStage.hpp"
#include "celestia/stages/ResolverStage.hpp"
#include "celestia/stages/Transpiler.hpp"

#include "src/CommandLine.hpp"

#include "celestia/semantic/resolver/Trace.hpp"

void show_diagnostics(std::vector<CompilationUnit *> units, CompilerEnvironment &env) {

  for (auto *unit : units) {
    for (auto &diag : unit->diagnostics.all()) { diagnostic::print_diagnostic(diag, unit->source, env); }
  }
}

int main(int argc, char *argv[]) {

  auto cmd = parse_command_line(argc, argv);

  if (cmd.command != Command::Run) return 0;

  if (!cmd.input) throw std::runtime_error("Nenhum arquivo informado.");

  auto lang = ayla::language::create_definition();

  Compiler compiler(lang);

  celestia::debug::Trace::enable(celestia::debug::Category::Resolver);
  celestia::debug::Trace::enable(celestia::debug::Category::Parser);

  auto bootstrap = compiler.create_frame();

  bootstrap.add_script("../src/ayla/scripts/types.ayla")
      .add_stage<ModuleBootstrapSetupStage>()
      .add_stage<LexerStage>()
      .add_stage<ParserStage>()
      .add_stage<ResolverStage>()
      .add_stage<LanguageBootstrapStage>()
      .add_stage<AstDumperStage>();

  bootstrap.run();

  show_diagnostics(bootstrap.units_, compiler.environment());

  auto user = compiler.create_frame();
  
  user.add_script(*cmd.input)
      .add_stage<LexerStage>()

      .add_stage<ParserStage>()
      .add_stage<ModuleSetupStage>()
      .add_stage<ResolverStage>()
      .add_stage<CheckStage>()
      .add_stage<LoweringStage>()
      .add_stage<CTranspilePass>();

  if (has_flag(cmd.dumps, DumpFlags::Ast)) { user.add_stage<AstDumperStage>(); }

  user.run();

  show_diagnostics(user.units_, compiler.environment());
}