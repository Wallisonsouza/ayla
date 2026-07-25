#include "AstDumper.hpp"

#include <format>

void AstDumper::dump_type(const ayla::ast::TypeNode *node) {
  auto g = context.object(std::format("Type(\"{}\")", node->name->str));

  g.list("Generics", node->generics);
}

void AstDumper::dump_object_field(const ayla::ast::node::ObjectFieldNode *node) {

  auto g = context.object("Field");

  g.field("Key", node->key);
  g.field("Value", node->value);
}