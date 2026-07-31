

#include "celestia/debug/ast/AstDumper.hpp"
#include <format>

void AstDumper::dump_identifier(const celestia::ast::IdentifierNode *node) {
  auto g = context.object(std::format("Identifier(\"{}\")", node->str));

  (void)g;
}

void AstDumper::dump_qualified_name(const celestia::ast::QualifiedNameNode *node) {
  auto g = context.object("QualifiedName");

  g.list("Parts", node->parts);
}