#include "celestia/transpiler/CGenerator.hpp"

namespace celestia::codegen {

void CGenerator::generate_field(const ast::FieldDeclaration *field) {
  if (!field || !field->name || !field->type) return;

  out << "    ";

   generate_type(field->type->type_id);

  out << " " << field->name->str << ";\n";
}

} // namespace celestia::codegen