#include "celestia/ast/declarations/FunctionDeclaration.hpp"
#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/core/visitor/Stage.hpp"

class LoweringStage : public Stage {
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    auto *module = unit.module;
    auto *script = unit.script;

    if (!script || script->statements.empty()) return;

    auto *main = unit.ast_arena.alloc<celestia::ast::FunctionDeclaration>();

    main->name = unit.ast_arena.alloc<celestia::ast::IdentifierNode>("__init__");

    main->body = script;

    module->declarations.push_back(main);

    unit.script = nullptr;
  }
};