#include "core/memory/BuiltinTypes.hpp"
#include "core/node/Type.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_index_access(parser::node::IndexAccessNode *node) {

  if (node->base) resolve(node->base);

  if (node->index) resolve(node->index);
}

void Resolver::resolve_member_access(parser::node::MemberAccessNode *node) {
  if (!node) return;

  resolve(node->base);

  Type *baseType = node->base->inferred_type;
  if (!baseType) return;

  if (baseType->kind != TypeKind::Object) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->field->slice);
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  auto *objType = static_cast<ObjectType *>(baseType);

  // 3) procurar membro
  auto *field = node->field;

  if (!objType->has_member(field->name)) {
    report_error(DiagnosticCode::UndeclaredSymbol, field->slice);
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  // 4) tipo do resultado
  node->inferred_type = objType->get_member(field->name);
}

void Resolver::resolve_function_call(parser::node::FunctionCallNode *node) {

  if (node->callee) resolve(node->callee);

  for (auto *arg : node->arguments) { resolve(arg); }
}