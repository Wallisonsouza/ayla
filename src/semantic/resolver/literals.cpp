#include "semantic/resolver/Resolver.hpp"

void Resolver::identifier(ayla::ast::node::IdentifierExpressionNode *node) {
  if (!node) return;

  SymbolId id = context.scopes.current()->symbol(node->name->str);

  if (!id.is_valid()) {
    // //report_error(DiagnosticCode::UndeclaredSymbol, node->slice);
    return;
  }

  node->resolved_symbol_id = id;
}

void Resolver::number_literal(ayla::ast::node::NumberLiteralNode *node) {}

void Resolver::string_literal(ayla::ast::node::StringLiteralNode *node) {}

void Resolver::boolean_literal(ayla::ast::node::BoolLiteralNode *node) {}

void Resolver::object_literal(ayla::ast::node::ObjectLiteralNode *node) {
  for (auto *field : node->fields) {
    if (field->value) resolve(field->value);
  }
}

void Resolver::array_literal(ayla::ast::node::ArrayLiteralNode *node) {
  for (auto *el : node->elements) resolve(el);
}
