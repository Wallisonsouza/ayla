
#include "celestia/transpiler/CGenerator.hpp"
#include <iostream>

namespace celestia::codegen {

void CGenerator::generate_expression(const ast::Expression *expr) {

  if (!expr) return;

  switch (expr->kind) {

  case ast::NodeKind::NumberLiteral: generate_number_literal(static_cast<const ast::NumberLiteralNode *>(expr)); return;

  case ast::NodeKind::StringLiteral: generate_string_literal(static_cast<const ast::StringLiteralNode *>(expr)); return;

  case ast::NodeKind::ArrayLiteral: generate_array_literal(static_cast<const ast::ArrayLiteralNode *>(expr)); return;

  case ast::NodeKind::StructLiteral: generate_struct_literal(static_cast<const ast::StructLiteralNode *>(expr)); return;

  case ast::NodeKind::BinaryExpression: generate_binary_expression(static_cast<const ast::BinaryExpressionNode *>(expr)); return;

  default: std::cerr << "[CGenerator] unsupported expression: " << ast::node_kind_name(expr->kind) << '\n'; return;
  }
}

} // namespace celestia::codegen