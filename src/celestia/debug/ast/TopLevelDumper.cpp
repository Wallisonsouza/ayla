#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/debug/ast/AstDumper.hpp"

#include <format>

namespace celestia::debug {

void AstDumper::dump_type(const ast::TypeNode *node) {

  if (!node) return;

  switch (node->kind) {

  case celestia::ast::NodeKind::NamedType: dump_named_type(static_cast<const ast::NamedType *>(node)); break;


  default: break;
  }
}

void AstDumper::dump_named_type(const ast::NamedType *node) {

  if (!node || !node->name) return;

  auto g = context.object(std::format("NamedType(\"{}\")", node->name->str));
}


void AstDumper::dump_generic_type(const ast::GenericTypeNode *node) {

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

} // namespace celestia::debug