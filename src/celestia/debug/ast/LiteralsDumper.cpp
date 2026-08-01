
#include "celestia/ast/expressions/LiteralExpressionNode.hpp"
#include "celestia/debug/ast/AstDumper.hpp"
#include <format>

void AstDumper::dump_number_literal(const celestia::ast::NumberLiteralNode *node) {
  auto g = context.object(std::format("Number({})", node->value));

  (void)g;
}

void AstDumper::dump_string_literal(const celestia::ast::StringLiteralNode *node) {
  auto g = context.object(std::format("String(\"{}\")", node->value));

  (void)g;
}

void AstDumper::dump_bool_literal(const celestia::ast::BoolLiteralNode *node) {
  auto g = context.object(std::format("Boolean({})", node->value ? "true" : "false"));

  (void)g;
}

void AstDumper::dump_null_literal(const celestia::ast::NullLiteralNode *node) {
  (void)node;

  auto g = context.object("Null");

  (void)g;
}

void AstDumper::dump_array_literal(const celestia::ast::ArrayLiteralNode *node) {
  auto g = context.object("ArrayLiteral");

  g.list("Elements", node->elements);
}

void AstDumper::dump_object_literal(const celestia::ast::ObjectLiteralNode *node) {
  auto g = context.object("ObjectLiteral");

  g.list("Fields", node->fields);
}