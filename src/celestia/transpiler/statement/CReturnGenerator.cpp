#include "celestia/transpiler/CGenerator.hpp"

namespace celestia::codegen {

void CGenerator::generate_return_statement(const ast::ReturnStatement *ret) {

  out << "  ";

  out << "return";

  if (ret->value) {
    out << " ";
    generate_expression(ret->value);
  }

  out << ";\n";
}

} // namespace celestia::codegen