#include "core/source/SourceManager.hpp"
#include "debug/engine/node/ast_debug.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/compilation_unit_manager.hpp"
#include "pipeline/Pipeline.hpp"
#include "runtime/ByteCode.hpp"
#include "runtime/Serealizer.hpp"
#include <iostream>
#include <memory>
#include <vector>

class CompilationSession {

  LanguageContext &context;

  CompilationUnitManager comp_manager;
  SourceManager source_manager;
  Pipeline pipeline;

public:
  CompilationSession(LanguageContext &ctx) : context(ctx) {}

  CompilationUnit &add_source(const std::string &path) {
    auto &src = source_manager.load(path);

    return comp_manager.create(context, src);
  }

  void add_pass(std::unique_ptr<Pass> pass) { pipeline.add_pass(std::move(pass)); }

  void run_pipeline() {

    for (auto &unit : comp_manager.units) {
      pipeline.run(*unit);
      BytecodeGenerator byteCode;
      byteCode.generate_ast(unit->ast.get_nodes());
      serialize_bytecode(context, byteCode);
    }
  }

  CompilationUnit &entry_unit() { return *comp_manager.units.front(); }
};
