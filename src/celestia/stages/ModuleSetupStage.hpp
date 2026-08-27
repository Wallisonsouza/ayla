#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/core/visitor/Stage.hpp"

class ModuleSetupStage : public Stage {
public:
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {
    if (!unit.ast_module) return;

    if (unit.module) return;

    auto name = unit.ast_module->name->get_name();

    unit.module = env.modules.register_module(name);

    if (!unit.module) throw std::runtime_error("failed to create module: " + name);
  }
};

class ModuleBootstrapSetupStage : public Stage {
public:
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {
    if (!unit.ast_module) return;

    unit.module = env.modules.builtin();

    if (!unit.module) throw std::runtime_error("builtin module not initialized");
  }
};