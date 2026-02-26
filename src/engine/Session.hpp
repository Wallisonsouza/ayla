#include "core/source/SourceManager.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/compilation_unit_manager.hpp"
#include "pipeline/Pipeline.hpp"
#include "runtime/AylaVM.hpp"
#include <memory>
#include <vector>

class CompilationSession {

  LanguageContext &context;

  CompilationUnitManager comp_manager;
  SourceManager source_manager;
  Pipeline pipeline;

public:
  CompilationSession(LanguageContext &ctx) : context(ctx) {}

  CompilationUnit &add_unity(const std::string &path) {
    auto &src = source_manager.load(path);
    return comp_manager.create(context, src);
  }

  void add_pass(std::unique_ptr<Pass> pass) { pipeline.add_pass(std::move(pass)); }

  void run_pipeline() {
    for (auto &unit : comp_manager.units) { pipeline.run(*unit); }
  }

  CompilationUnit &entry_unit() { return *comp_manager.units.front(); }
};

// auto ptr = std::make_shared<GenModule>();

// auto byte_code = BytecodeGenerator(ptr.get());

// for (auto &unit : comp_manager.units) {
//   byte_code.generate_ast(unit->ast.get_nodes());
//   byte_code.finalize_script();
// }

// byte_code.print_bytecode();
// // AylaVM vm;
// // vm.execute(*ptr);