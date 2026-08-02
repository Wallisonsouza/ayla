
#include "celestia/debug/ast/AstDumper.hpp"
#include <format>

namespace celestia::debug {
void AstDumper::dump_type(const ast::TypeNode *node) {
  auto g = context.object(std::format("Type(\"{}\")", node->name->str));

  g.list("Generics", node->generics);
}

void AstDumper::dump_object_field(const ast::ObjectFieldNode *node) {

  auto g = context.object("Field");

  g.field("Key", node->key);
  g.field("Value", node->value);
}
} // namespace celestia::debug