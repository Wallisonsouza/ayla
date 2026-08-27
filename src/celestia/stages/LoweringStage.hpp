
#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/core/visitor/Stage.hpp"

class LoweringStage : public Stage {
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    // auto *module = unit.module;
    // auto *script = unit.script;

    // if (!module || !script || script->statements.empty()) return;

    // auto *init = unit.ast_arena.alloc<celestia::ast::ModuleInitDeclaration>(script);

    // module->declarations.push_back(init);

    // unit.script = nullptr;
  }
};