
#include "celestia/debug/ast/AstDumper.hpp"
#include <format>

void AstDumper::dump_type(const celestia::ast::TypeNode *node) {
  auto g = context.object(std::format("Type(\"{}\")", node->name->str));

  g.list("Generics", node->generics);
}

void AstDumper::dump_object_field(const celestia::ast::ObjectFieldNode *node) {

  auto g = context.object("Field");

  g.field("Key", node->key);
  g.field("Value", node->value);
}