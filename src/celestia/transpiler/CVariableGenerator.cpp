#include "CGenerator.hpp"
#include "celestia/ast/declarations/VariableDeclaration.hpp"

namespace celestia::codegen {

void CGenerator::generate_variable_declaration(const ast::VariableDeclaration *variable) {

  if (!variable || !variable->pattern) return;

  out << "    ";

  generate_pattern(variable->pattern);

  if (variable->initializer) {
    out << " = ";
    generate_expression(variable->initializer);
  }

  out << ";\n";
}

} // namespace celestia::codegen