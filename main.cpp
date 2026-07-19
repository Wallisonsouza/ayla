#include "core/managers/source_manager.hpp"
#include "diagnostic/formatter.hpp"
#include "engine/CompilationUnit.hpp"
#include "context/argon_main.hpp"
#include "engine/Pass.hpp"
#include "engine/compilation_unit_manager.hpp"
#include "runtime/bytecode/Serealizer.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "engine/LexerPass.hpp"


class PhaseManager {
  std::vector<std::unique_ptr<Pass>> phases;
public:
  void add_phase(std::unique_ptr<Pass> phase) {
    phases.push_back(std::move(phase));
  }
  void run_phases(CompilationUnit &unit) {
    for (auto &phase : phases) {
       phase->run(unit);
    }
  }
};

class CompilationSession {

  LanguageContext &context;

  SourceManager src_manager;
  CompilationUnitManager cu_manage;
  PhaseManager phase_manager;
  
  public:
  explicit CompilationSession(LanguageContext &ctx) : context(ctx) {}


  CompilationUnit* add_unit(const std::string &path) {
      
    auto source = src_manager.create_source(path);

    return cu_manage.create_compilation_unit(context, *source);
  }

  void add_pass(std::unique_ptr<Pass> pass) {
    phase_manager.add_phase(std::move(pass));
  };
  
  void compile() {

    for(auto &unit : cu_manage.units) {
      phase_manager.run_phases(*unit);
    }
  }

  void show_diagnostics(CompilationUnit &unit) {
    for (auto &diag : unit.diagns.all()) { print(*diag, unit); }
  }

  // void show_all_diagnostics() {
  //   for (auto &unit : cu_manage.arena) { show_diagnostics(*unit); }
  // }

};

int main() {

  auto context = ayla::language::create_context();

  CompilationSession session(context);

  session.add_pass(std::make_unique<LexerPass>());
  session.add_pass(std::make_unique<ParsePass>());
  session.add_pass(std::make_unique<DebugPass>());

  session.add_unit("../scripts/main.ayla");

  session.compile();


  std::cout << "compilou essa merda de projeto";
  return 0;
}

