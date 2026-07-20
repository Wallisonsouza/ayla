#include "core/managers/source_manager.hpp"
#include "diagnostic/formatter.hpp"
#include "engine/LangContext.hpp"
#include "engine/Pass.hpp"
#include "engine/UnitManager.hpp"
#include "engine/LangContext.hpp"
#include "PhaseManager.hpp"

class CompilationSession {

  LanguageContext &context;

  SourceManager src_manager;
  CompilationUnitManager cu_manage;
  PhaseManager phase_manager;
  
  public:
  explicit CompilationSession(LanguageContext &ctx) : context(ctx) {}


  CompilationUnit* add_script(const std::string &path) {
      
    auto *source = src_manager.create_source(path);

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
};
