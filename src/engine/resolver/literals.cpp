#include "core/memory/BuiltinTypes.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_number_literal(parser::node::NumberLiteralNode *node) { node->inferred_type = &BuiltinTypes::Number; }

void Resolver::resolve_string_literal(parser::node::StringLiteralNode *node) { node->inferred_type = &BuiltinTypes::String; }

void Resolver::resolve_boolean_literal(parser::node::BoolLiteralNode *node) { node->inferred_type = &BuiltinTypes::Boolean; }

void Resolver::resolve_object_literal(parser::node::ObjectLiteralNode *node) {

  auto *obj_type = unit.type_arena.alloc<ObjectType>();

  for (auto *field : node->field_list->elements) {

    if (field->value) resolve(field->value);

    if (!field->key || field->key->kind != core::ast::NodeKind::Identifier) continue;

    auto *key = static_cast<core::ast::IdentifierNode *>(field->key);

    if (obj_type->has_member(key->name)) {
      report_error(DiagnosticCode::RedeclaredIdentifier, key->slice);
      continue;
    }

    Type *valueType = field->value && field->value->inferred_type ? field->value->inferred_type : &BuiltinTypes::Unknown;

    obj_type->add_member(key->name, valueType);
  }

  node->inferred_type = obj_type;
}

void Resolver::resolve_array_literal(parser::node::ASTArrayLiteralNode *node) {
  if (!node) return;

  Type *elementType = nullptr;

  for (auto *el : node->elements) {
    resolve(el);

    Type *t = el->inferred_type ? el->inferred_type : &BuiltinTypes::Unknown;

    if (!elementType) {
      elementType = t;
    } else if (elementType != t) {
      elementType = &BuiltinTypes::Unknown;
    }
  }

  if (!elementType) elementType = &BuiltinTypes::Unknown;

  node->inferred_type = unit.type_arena.alloc<ArrayType>(elementType);
}