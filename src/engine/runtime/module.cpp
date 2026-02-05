#include "engine/runtime/executor.hpp"
#include <iostream>

ExecResult Executor::execute_module_declaration(CompilationUnit &unit, ayla::ast::node::ModuleDeclarationNode *node) { return ExecResult::make_value(std::make_shared<Value>(Value::Void())); }

ExecResult Executor::execute_import_node(CompilationUnit &unit, ayla::ast::node::ImportStatementNode *node) {

  auto module = unit.context.module_manager.get(node->resolved_module_id);

  if (!module) { throw std::runtime_error("Module not found: "); }

  module->ensure_initialized();

  core::ParserScope *pscope = module->parser_scope;

  std::cout << "symbol size : " << unit.context.symbol_manager.symbols.size();

  for (auto &symbol : unit.context.symbol_manager.symbols) {
    //
    std::cout << "symbol: " << symbol.name << "\n";
  }

  // for (auto &[name, id] : pscope->table) {
  //   Symbol *sym = unit.context.symbol_manager.get(id);
  //   if (sym) {
  //     std::cout << "symbol: " << name << " kind: " << (int)sym->kind << "\n";
  //   } else {
  //     std::cout << "symbol id " << id.value << " " << name << " not found in global SymbolManager\n";
  //   }
  // }

  return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
}