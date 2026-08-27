#include "celestia/transpiler/CGenerator.hpp"
#include <iostream>

namespace celestia::codegen {

void CGenerator::generate_binary_expression(const ast::BinaryExpressionNode *expr) {

  if (!expr) return;

  generate_expression(expr->lhs);

  out << ' ';

  switch (expr->op) {

  case BinaryOperation::Add: out << '+'; break;

  case BinaryOperation::Subtract: out << '-'; break;

  case BinaryOperation::Multiply: out << '*'; break;

  case BinaryOperation::Divide: out << '/'; break;

  case BinaryOperation::Equal: out << "=="; break;

  case BinaryOperation::NotEqual: out << "!="; break;

  case BinaryOperation::Less: out << '<'; break;

  case BinaryOperation::LessEqual: out << "<="; break;

  case BinaryOperation::Greater: out << '>'; break;

  case BinaryOperation::GreaterEqual: out << ">="; break;

  case BinaryOperation::And: out << "&&"; break;

  case BinaryOperation::Or: out << "||"; break;

  default: std::cerr << "[CGenerator] unsupported binary operator\n"; return;
  }

  out << ' ';

  generate_expression(expr->rhs);
}
} // namespace celestia::codegen