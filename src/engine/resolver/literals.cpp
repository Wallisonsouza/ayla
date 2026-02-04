#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_identifier(core::ast::IdentifierNode *node) {
  if (!node) return;

  SymbolId id = current_scope->resolve_symbol(node->name);

  if (!id.is_valid()) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->slice);
    return;
  }

  node->resolved_symbol_id = id;
}

void Resolver::resolve_number_literal(parser::node::NumberLiteralNode *node) {}

void Resolver::resolve_string_literal(parser::node::StringLiteralNode *node) {}

void Resolver::resolve_boolean_literal(parser::node::BoolLiteralNode *node) {}

void Resolver::resolve_object_literal(parser::node::ObjectLiteralNode *node) {
  for (auto *field : node->field_list->elements) {
    if (field->value) resolve(field->value);
  }
}

void Resolver::resolve_array_literal(parser::node::ASTArrayLiteralNode *node) {
  for (auto *el : node->elements) resolve(el);
}

void Resolver::resolve_type_node(core::ast::TypeNode *node) {
  if (!node || !node->identifier) return;

  resolve_identifier(node->identifier);

  SymbolId sym_id = current_scope->resolve_symbol(node->identifier->name);

  if (sym_id == INVALID_SYMBOL_ID) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->identifier->slice, {{"name", node->identifier->name}});
    node->symbol_id = INVALID_SYMBOL_ID;
    return;
  }

  node->symbol_id = sym_id;

  for (auto *generic : node->generics) { resolve_type_node(generic); }
}