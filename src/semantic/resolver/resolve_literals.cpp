#include "semantic/resolver/Resolver.hpp"

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