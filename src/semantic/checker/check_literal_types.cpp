#include "semantic/checker/TypeChecker.hpp"
namespace ayla {
void TypeChecker::check_array_literal(ast::node::ArrayLiteralNode *node) {
  if (!node) return;

  Type *elementType = nullptr;
  for (auto *el : node->elements) {
    check(el);
    Type *t = el->inferred_type ? el->inferred_type : &BuiltinTypes::Unknown;

    if (!elementType)
      elementType = t;
    else if (elementType != t)
      elementType = &BuiltinTypes::Unknown;
  }

  if (!elementType) elementType = &BuiltinTypes::Unknown;

  node->inferred_type = unit.context.type_arena.alloc<ArrayType>(elementType);
}

void TypeChecker::check_object_literal(ast::node::ObjectLiteralNode *node) {
  if (!node) return;

  auto *objType = unit.context.type_arena.alloc<ObjectType>();

  for (auto *field : node->fields) {
    check(field->value);

    if (!field->key || field->key->kind != ast::NodeKind::Identifier) continue;
    auto *key = static_cast<ast::node::IdentifierExpressionNode *>(field->key);

    if (objType->has_member(key->name)) {
      report_error(DiagnosticCode::RedeclaredIdentifier, key->slice);
      continue;
    }

    Type *valueType = field->value ? field->value->inferred_type : &BuiltinTypes::Unknown;
    objType->add_member(key->name, valueType);
  }

  node->inferred_type = objType;
}
} // namespace ayla
