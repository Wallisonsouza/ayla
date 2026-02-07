#include "frontend/symbols/SymbolId.hpp"
#include "runtime/interpreter/executor.hpp"
#include "runtime/value/value.hpp"

ExecResult Executor::execute_module_declaration(CompilationUnit &unit, ayla::ast::node::ModuleDeclarationNode *node) { return ExecResult::make_value(std::make_shared<Value>(Value::Void())); }

ExecResult Executor::execute_import_node(CompilationUnit &unit, ayla::ast::node::ImportStatementNode *node) {

  auto module = unit.context.module_manager.get(node->resolved_module_id);

  if (!module) throw std::runtime_error("Module not found");

  module->ensure_initialized();

  current_scope->set(node->resolved_symbol_id, module->module_object);

  return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
}
