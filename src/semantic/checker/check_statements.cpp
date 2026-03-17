
#include "ayla/semantic/checker/checker.hpp"
namespace ayla {

void ayla::semantic::Checker::check_function_declaration(ast::node::FunctionDeclarationNode *node) {
  if (!node) return;

  current_function_return_type = node->return_type ? node->return_type->inferred_type : nullptr;

  for (auto *param : node->parameters) check_pattern(param);

  if (node->body) check_block_statement(node->body);

  auto *ft = unit.context.type_arena.alloc<FunctionType>();
  for (auto *param : node->parameters) ft->params.push_back(param->inferred_type);

  ft->return_type = node->return_type ? node->return_type->inferred_type : (current_function_return_type ? current_function_return_type : &BuiltinTypes::Unknown);

  node->inferred_type = ft;
  if (auto *sym = unit.context.symbol_manager.get(node->symbol_id)) sym->type = ft;

  current_function_return_type = nullptr;
}

void ayla::semantic::Checker::check_module_declaration(ayla::ast::node::ModuleDeclarationNode *node) {
  if (!node) return;

  auto *module = unit.context.module_manager.get(node->resolved_module_id);
  if (!module) return;

  module->type = unit.context.type_arena.alloc<ModuleType>();

  for (auto *stmt : node->body) {

    if (!stmt) continue;

    check(stmt);

    if (auto *fn = dynamic_cast<ayla::ast::node::FunctionDeclarationNode *>(stmt)) {

      if (fn->identifier) module->type->add_member(fn->identifier->name, fn->inferred_type);
    }
  }

  node->inferred_type = module->type;

  if (auto *sym = unit.context.symbol_manager.get(node->resolved_symbol_id)) { sym->type = module->type; }
}

void ayla::semantic::Checker::check_variable_declaration(ast::node::VariableDeclarationNode *node) {
  if (!node) return;

  if (node->initializer) { check(node->initializer); }

  check_pattern(node->pattern);

  auto *idPattern = dynamic_cast<ast::IdentifierPatternNode *>(node->pattern);
  if (!idPattern) return;

  if (idPattern->type_annotation) { auto type = unit.context.type_table.find(idPattern->type_annotation->name); }

  Type *finalType = nullptr;

  if (idPattern->type_annotation)
    finalType = idPattern->type_annotation->inferred_type;
  else if (node->initializer)
    finalType = node->initializer->inferred_type;
  else
    finalType = &BuiltinTypes::Unknown;

  idPattern->inferred_type = finalType;

  if (auto *sym = unit.context.symbol_manager.get(idPattern->symbol_id)) sym->type = finalType; // ✅ Atualiza o símbolo com tipo final
}

// statements
void ayla::semantic::Checker::check_if_statement(ast::node::IfStatementNode *node) {
  check(node->condition);
  // if (node->condition->inferred_type != &BuiltinTypes::Boolean) report_error(DiagnosticCode::TypeMismatch, node->condition->slice);

  check(node->then_block);
  if (node->else_block) check(node->else_block);

  node->inferred_type = &BuiltinTypes::Unknown;
}

void ayla::semantic::Checker::check_while_statement(ast::node::WhileStatementNode *node) {
  check(node->condition);
  // if (node->condition->inferred_type != &BuiltinTypes::Boolean) report_error(DiagnosticCode::TypeMismatch, node->condition->slice);

  check(node->body);

  node->inferred_type = &BuiltinTypes::Unknown;
}

void ayla::semantic::Checker::check_block_statement(ast::node::BlockStatementNode *node) {
  if (!node) return;

  for (auto *stmt : node->statements) check(stmt);

  node->inferred_type = &BuiltinTypes::Unknown;
}

void ayla::semantic::Checker::check_expression_statement(ast::node::ExpressionStatementNode *node) {
  if (!node || !node->expression) return;
  check(node->expression);
}

void ayla::semantic::Checker::check_return_statement(ast::node::ReturnStatementNode *node) {
  if (!node->value) return;

  check(node->value);
  Type *actual = node->value->inferred_type ? node->value->inferred_type : &BuiltinTypes::Unknown;

  if (!current_function_return_type) {
    current_function_return_type = actual;
  } else if (actual != current_function_return_type) {

    // report_error(DiagnosticCode::TypeMismatch, node->slice);
  }

  node->inferred_type = actual;
}

void ayla::semantic::Checker::check_import_statement(ayla::ast::node::ImportStatementNode *node) {

  if (!node) return;

  auto *module = unit.context.module_manager.get(node->resolved_module_id);
  if (!module) {
    // report_error(DiagnosticCode::ModuleNotFound, node->slice);
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  node->inferred_type = module->type;

  if (auto *sym = unit.context.symbol_manager.get(node->resolved_symbol_id)) { sym->type = node->inferred_type; }
}

} // namespace ayla
