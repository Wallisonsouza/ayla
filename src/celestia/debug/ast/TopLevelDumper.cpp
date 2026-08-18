#include "celestia/ast/types/Array.hpp"
#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/debug/ast/AstDumper.hpp"

#include <format>

namespace celestia::debug {

void AstDumper::dump_type(const ast::TypeNode *node) {

  if (!node) return;

  switch (node->kind) {

  case celestia::ast::NodeKind::NamedType: dump_named_type(static_cast<const ast::NamedType *>(node)); break;

  case celestia::ast::NodeKind::ArrayType: dump_array_type(static_cast<const ast::ArrayType *>(node)); break;

  case celestia::ast::NodeKind::GenericType: dump_generic_type(static_cast<const ast::GenericType *>(node)); break;

  default: break;
  }
}

void AstDumper::dump_named_type(const ast::NamedType *node) {

  if (!node || !node->name) return;

  auto g = context.object(std::format("NamedType(\"{}\")", node->name->str));
}

void AstDumper::dump_array_type(const ast::ArrayType *node) {

  if (!node) return;

  auto g = context.object("ArrayType");

  g.field("ElementType", node->element_type);
}

void AstDumper::dump_generic_type(const ast::GenericType *node) {

  if (!node || !node->name) return;

  auto g = context.object(std::format("GenericType(\"{}\")", node->name->str));

  g.list("Arguments", node->arguments);
}

void AstDumper::dump_object_field(const ast::ObjectFieldNode *node) {

  if (!node) return;

  auto g = context.object("Field");

  g.field("Key", node->key);
  g.field("Value", node->value);
}

void AstDumper::dump_reference_type(const ast::ReferenceType *node) {

  if (!node) return;

  auto g = context.object("ReferenceType");

  g.field("Target", node->target);
}
} // namespace celestia::debug