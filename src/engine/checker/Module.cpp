#include "TypeChecker.hpp"

void TypeChecker::check_module_declaration(parser::node::statement::ModuleDeclarationNode *node) {
  if (!node) return;

  auto *module = unit.context.module_manager.get(node->resolved_module_id);
  if (!module) return;

  module->type = unit.type_arena.alloc<ModuleType>();

  for (auto *stmt : node->body) {

    if (!stmt) continue;

    check(stmt);

    if (auto *fn = dynamic_cast<parser::node::FunctionDeclarationNode *>(stmt)) {

      if (fn->identifier) module->type->add_member(fn->identifier->name, fn->inferred_type);
    }

    if (auto *var = dynamic_cast<ayla::ast::PatternNode *>(stmt)) {
      if (var->identifier) module->type->add_member(var->identifier->name, var->inferred_type);
    }
  }

  node->inferred_type = module->type;

  if (auto *sym = unit.context.symbol_manager.get(node->resolved_symbol_id)) { sym->type = module->type; }
}

void TypeChecker::check_import_node(parser::node::statement::ImportNode *node) {
  if (!node) return;

  auto *module = unit.context.module_manager.get(node->resolved_module_id);
  if (!module) {
    report_error(DiagnosticCode::ModuleNotFound, node->slice);
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  node->inferred_type = module->type;
  if (auto *sym = unit.context.symbol_manager.get(node->resolved_symbol_id)) { sym->type = node->inferred_type; }
}