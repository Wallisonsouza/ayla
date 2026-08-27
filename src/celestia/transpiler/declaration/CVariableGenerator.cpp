#include "celestia/ast/declarations/VariableDeclaration.hpp"
#include "celestia/transpiler/CGenerator.hpp"

namespace celestia::codegen {

void CGenerator::generate_variable_declaration(const ast::VariableDeclaration *variable) {

  if (!variable || !variable->pattern) return;

  auto *pattern = static_cast<const ast::NamedPattern *>(variable->pattern);

  if (!pattern->symbol_id.is_valid()) return;

  auto *symbol = context.compiler.symbols.get(pattern->symbol_id);

  if (!symbol || !symbol->type.is_valid()) return;

  generate_type(symbol->type);

  out << " ";

  out << pattern->name->str;

  if (variable->initializer) {

    out << " = ";

    generate_expression(variable->initializer);
  }

  out << ";\n";
}

} // namespace celestia::codegen