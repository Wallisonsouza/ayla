#include "engine/resolver/Resolver.hpp"
#include <iostream>

void Resolver::resolve_identifier(ayla::ast::node::IdentifierExpressionNode *node) {
  if (!node) return;

  SymbolId id = current_scope->resolve_symbol(node->name);

  if (!id.is_valid()) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->slice);
    return;
  }

  node->resolved_symbol_id = id;
  std::cout << "Resolved identifier '" << node->name << "' to symbol_id " << id.value << "\n";
}

void Resolver::resolve_number_literal(ayla::ast::node::NumberLiteralNode *node) {}

void Resolver::resolve_string_literal(ayla::ast::node::StringLiteralNode *node) {}

void Resolver::resolve_boolean_literal(ayla::ast::node::BoolLiteralNode *node) {}

void Resolver::resolve_object_literal(ayla::ast::node::ObjectLiteralNode *node) {
  for (auto *field : node->fields) {
    if (field->value) resolve(field->value);
  }
}

void Resolver::resolve_array_literal(ayla::ast::node::ArrayLiteralNode *node) {
  for (auto *el : node->elements) resolve(el);
}

void Resolver::resolve_type_node(ayla::ast::TypeNode *node) {
  if (!node || !node->identifier) return;

  resolve_identifier(node->identifier);

  SymbolId sym_id = current_scope->resolve_symbol(node->identifier->name);

  if (!sym_id.is_valid()) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->identifier->slice, {{"name", node->identifier->name}});
    return;
  }

  node->symbol_id = sym_id;

  for (auto *generic : node->generics) { resolve_type_node(generic); }
}