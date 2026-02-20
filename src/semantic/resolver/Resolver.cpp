#include "Resolver.hpp"
#include "ast/expressions/UnaryExpressionNode.hpp"
#include "core/node/flags.hpp"

void Resolver::resolve(ayla::ast::AstNode *node) {

  if (!node || node->flags.has(NodeFlags::Resolved)) return;

  node->flags.set(NodeFlags::Resolved);

  switch (node->kind) {

  case ayla::ast::NodeKind::NumberLiteral:
    resolve_number_literal(static_cast<ayla::ast::node::NumberLiteralNode *>(node));
    break;

  case ayla::ast::NodeKind::StringLiteral:
    resolve_string_literal(static_cast<ayla::ast::node::StringLiteralNode *>(node));
    break;

  case ayla::ast::NodeKind::BooleanLiteral:
    resolve_boolean_literal(static_cast<ayla::ast::node::BoolLiteralNode *>(node));
    break;

  case ayla::ast::NodeKind::IfStatement:
    resolve_if_statement(static_cast<ayla::ast::node::IfStatementNode *>(node));
    break;

  case ayla::ast::NodeKind::WhileStatement:
    resolve_while_statement(static_cast<ayla::ast::node::WhileStatementNode *>(node));
    break;

  case ayla::ast::NodeKind::BlockStatement:
    resolve_block_statement(static_cast<ayla::ast::node::BlockStatementNode *>(node));
    break;

  case ayla::ast::NodeKind::BinaryExpression:
    resolve_binary_exp(static_cast<ayla::ast::node::BinaryExpressionNode *>(node));
    break;

  case ayla::ast::NodeKind::MemberAccessExpression:
    resolve_member_exp(static_cast<ayla::ast::node::MemberAccessExpressionNode *>(node));
    break;

  case ayla::ast::NodeKind::ImportStatement:
    resolve_import_node(static_cast<ayla::ast::node::ImportStatementNode *>(node));
    break;

  case ayla::ast::NodeKind::Identifier:
    resolve_identifier_exp(static_cast<ayla::ast::node::IdentifierExpressionNode *>(node));
    break;

  case ayla::ast::NodeKind::CallExpression:
    resolve_call_exp(static_cast<ayla::ast::node::CallExpressionNode *>(node));
    break;

  case ayla::ast::NodeKind::ExpressionStatement:
    resolve_expression_statement(static_cast<ayla::ast::node::ExpressionStatementNode *>(node));
    break;

  case ayla::ast::NodeKind::VariableDeclaration:
    resolve_variable_declaration(static_cast<ayla::ast::node::VariableDeclarationNode *>(node));
    break;

  case ayla::ast::NodeKind::FunctionDeclaration:
    resolve_function_declaration(static_cast<ayla::ast::node::FunctionDeclarationNode *>(node));
    break;

  case ayla::ast::NodeKind::ModuleDeclaration:
    resolve_module_declaration(static_cast<ayla::ast::node::ModuleDeclarationNode *>(node));
    break;

  case ayla::ast::NodeKind::ReturnStatement:
    resolve_return_statement(static_cast<ayla::ast::node::ReturnStatementNode *>(node));
    break;

  case ayla::ast::NodeKind::Assignment:
    resolve_assign_exp(static_cast<ayla::ast::node::AssignmentExpressionNode *>(node));
    break;

  case ayla::ast::NodeKind::ArrayLiteral:
    resolve_array_literal(static_cast<ayla::ast::node::ArrayLiteralNode *>(node));
    break;

  case ayla::ast::NodeKind::IndexAccess:
    resolve_index_exp(static_cast<ayla::ast::node::IndexAccessExpressionNode *>(node));
    break;

  case ayla::ast::NodeKind::ObjectLiteral:
    resolve_object_literal(static_cast<ayla::ast::node::ObjectLiteralNode *>(node));
    break;

  case ayla::ast::NodeKind::Type:
    resolve_type_node(static_cast<ayla::ast::TypeNode *>(node));
    break;

  case ayla::ast::NodeKind::UnaryExpression:
    resolve_unary_exp(static_cast<ayla::ast::node::UnaryExpressionNode *>(node));
    break;

  default:
    break;
  }
}

void Resolver::push_scope() { current_scope = unit.scope_manager.create_scope(current_scope); }

void Resolver::pop_scope() { current_scope = current_scope->parent; }

// blocos e funções

void Resolver::resolve_pattern(ayla::ast::PatternNode *pat, ayla::ast::Modifiers modifier) {
  if (!pat) return;

  switch (pat->kind) {
  case ayla::ast::NodeKind::IdentifierPattern: {
    auto *pattern = static_cast<ayla::ast::IdentifierPatternNode *>(pat);

    // Verifica redeclaração
    if (current_scope->has_symbol_local(pattern->identifier->name)) {
      report_error(DiagnosticCode::RedeclaredIdentifier, pattern->identifier->slice, {{"name", pattern->identifier->name}});
      return;
    }

    // Cria símbolo
    SymbolId symbol_id = unit.context.symbol_manager.create_symbol(pattern->identifier->name, SymbolKind::Variable, Visibility::Private, false, pat);

    auto symbol = unit.context.symbol_manager.get(symbol_id);
    symbol->modifiers = modifier;

    // Declara no scope atual
    current_scope->declare(pattern->identifier->name, symbol_id);

    // Slot da variável: se não houver, aloca temporário
    pattern->symbol_id = symbol_id;
    pattern->local_slot = current_scope->resolve_slot(symbol_id).value_or(0);

    // Atualiza a expressão identificadora associada
    pattern->identifier->resolved_symbol_id = pattern->symbol_id;
    pattern->identifier->local_slot = pattern->local_slot;

    // Resolve tipo se houver anotação
    if (pattern->type_annotation) resolve_type_node(pattern->type_annotation);

    break;
  }

  default:
    break;
  }
}
void Resolver::resolve_module_declaration(ayla::ast::node::ModuleDeclarationNode *node) {
  if (!node || node->path.empty()) return;

  ModuleId module_id = unit.context.module_manager.get_or_create_module_path(node->path);
  auto module = unit.context.module_manager.get(module_id);
  node->resolved_module_id = module_id;

  std::string module_name = node->path.back()->name;

  module->parser_scope = unit.scope_manager.create_scope(nullptr);

  auto *prev = current_scope;
  current_scope = module->parser_scope;

  for (auto *stmt : node->body) resolve(stmt);

  current_scope = prev;
}

void Resolver::resolve_import_node(ayla::ast::node::ImportStatementNode *node) {
  if (!node || node->path.empty()) return;

  size_t failed_index;
  ModuleId module_id = unit.context.module_manager.find_path(node->path, failed_index);

  if (module_id == INVALID_MODULE) {
    report_error(DiagnosticCode::ModuleNotFound, node->slice, {{"name", node->path[failed_index]->name}});
    return;
  }

  node->resolved_module_id = module_id;

  auto module = unit.context.module_manager.get(module_id);

  std::string local_name = node->alias.value_or(node->path.back()->name);

  if (current_scope->has_symbol_local(local_name)) {
    report_error(DiagnosticCode::RedeclaredIdentifier, node->slice, {{"name", local_name}});
    return;
  }

  SymbolId sym_id = unit.context.symbol_manager.create_symbol(local_name, SymbolKind::Module, Visibility::Public, true, node);

  unit.context.symbol_manager.get(sym_id)->module_id = module_id;

  current_scope->declare(local_name, sym_id);

  node->resolved_symbol_id = sym_id;
}
