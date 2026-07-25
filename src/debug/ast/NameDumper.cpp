#include "AstDumper.hpp"

#include <format>

void AstDumper::dump_identifier(const ayla::ast::IdentifierNode *node) {
  auto g = context.object(std::format("Identifier(\"{}\")", node->str));

  (void)g;
}

void AstDumper::dump_qualified_name(const ayla::ast::QualifiedNameNode *node) {
  auto g = context.object("QualifiedName");

  g.list("Parts", node->parts);
}