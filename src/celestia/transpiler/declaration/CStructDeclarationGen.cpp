#include "celestia/transpiler/CGenerator.hpp"
#include <iostream>

namespace celestia::codegen {

void CGenerator::generate_struct_declaration(const ast::StructDeclaration *decl) {

  if (!decl || !decl->name) return;

  if (!decl->type_id.is_valid()) {
    std::cerr << "[CGenerator] struct has no resolved type\n";
    return;
  }

  const auto &type = context.compiler.types.get(decl->type_id);

  if (type.kind != semantic::TypeKind::Struct) {
    std::cerr << "[CGenerator] declaration is not a struct type\n";
    return;
  }

  const auto &struct_type = static_cast<const semantic::StructType &>(type);

  out << "struct " << decl->name->str << " {\n";

  for (const auto &[name, type_id] : struct_type.members) {

    out << "    ";

    generate_type(type_id);

    out << " " << name << ";\n";
  }

  out << "};\n\n";
}

} // namespace celestia::codegen