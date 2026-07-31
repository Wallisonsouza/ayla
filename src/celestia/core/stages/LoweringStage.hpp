#include "celestia/ast/declarations/FunctionDeclarationNode.hpp"
#include "celestia/core/visitor/Stage.hpp"
#include "celestia/engine/CompilationUnit.hpp"
#include "celestia/engine/CompilerEnvironment.hpp"
#include <iostream>

class LoweringStage : public Stage {
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    auto *module = unit.module;
    auto *script = unit.script;

    if (!script || script->statements.empty()) return;


    auto *main = unit.ast.create_node<celestia::ast::node::FunctionDeclarationNode>();

    main->name = unit.ast.create_node<celestia::ast::IdentifierNode>("main");

    main->body = script;

    module->declarations.push_back(main);

    unit.script = nullptr;
  }
};