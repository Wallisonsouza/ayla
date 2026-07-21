#include "ast/names/QualifiedNameNode.hpp"
#include "AstDumper.hpp"
#include <format>

void AstDumper::debug_name(const ayla::ast::NameNode *node) { debug_header(std::format("Identifier(\"{}\")", node->str)); }

void AstDumper::debug_type(const ayla::ast::TypeNode *node) {

  debug_header(std::format("Type(\"{}\")", node->name->str));

  size_t count = node->generics.size();
  for (size_t i = 0; i < count; ++i) { debug_node(node->generics[i], i == count - 1); }
}


void AstDumper::debug_object_field(const ayla::ast::node::ObjectFieldNode *node) {
  out << "Field\n";

  if (node->key) { debug_node(node->key, false); }

  if (node->value) { debug_node(node->value, true); }
}
