#include "celestia/transpiler/CGenerator.hpp"

namespace celestia::codegen {


void CGenerator::generate_number_literal(const ast::NumberLiteralNode *literal) {

  if (!literal) return;

  out << literal->value;
}

void CGenerator::generate_string_literal(const ast::StringLiteralNode *literal) {

  if (!literal) return;

  out << literal->value;
}

} // namespace celestia::codegen