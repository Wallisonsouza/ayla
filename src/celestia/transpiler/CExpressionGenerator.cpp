#include "CGenerator.hpp"

#include "celestia/ast/expressions/LiteralExpressionNode.hpp"

namespace celestia::codegen {

void CGenerator::generate_number_literal(const ast::NumberLiteralNode *literal) {

  if (!literal) return;

  out << literal->value;
}

void CGenerator::generate_string_literal(const ast::StringLiteralNode *literal) {

  if (!literal) return;

  out << literal->value;
}

void CGenerator::generate_array_literal(const ast::ArrayLiteralNode *literal) {
  if (!literal) return;

  const size_t size = literal->elements.size();


  if (size == 0) {
    out << "ayla_array_make(sizeof(int))";
    return;
  }

  out << "ayla_array_from((int[]){";

  bool first = true;

  for (auto *element : literal->elements) {
    if (!element) continue;

    if (!first) out << ", ";

    first = false;

    generate_expression(element);
  }

  out << "}, ";
  out << size;
  out << ", sizeof(int))";
}

void CGenerator::generate_expression(const ast::Expression *expr) {

  if (!expr) return;

  switch (expr->kind) {

  case ast::NodeKind::NumberLiteral: generate_number_literal(static_cast<const ast::NumberLiteralNode *>(expr)); return;

  case ast::NodeKind::StringLiteral: generate_string_literal(static_cast<const ast::StringLiteralNode *>(expr)); return;

  case ast::NodeKind::ArrayLiteral: generate_array_literal(static_cast<const ast::ArrayLiteralNode *>(expr)); return;

  case ast::NodeKind::StructLiteral: generate_struct_literal(static_cast<const ast::StructLiteralNode *>(expr)); return;

  default: return;
  }
}

} // namespace celestia::codegen