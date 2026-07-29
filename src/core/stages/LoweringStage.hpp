#include "ast/declarations/FunctionDeclarationNode.hpp"
#include "core/visitor/Stage.hpp"
#include "engine/CompilationUnit.hpp"
#include <iostream>

class LoweringStage : public Stage {
  void run(CompilationUnit &unit) override {

    auto *module = unit.module;
    auto *script = unit.script;

    if (!script || script->statements.empty()) return;


    auto *main = unit.ast.create_node<ayla::ast::node::FunctionDeclarationNode>();

    main->name = unit.ast.create_node<ayla::ast::IdentifierNode>("main");

    main->body = script;

    module->declarations.push_back(main);

    unit.script = nullptr;
  }
};