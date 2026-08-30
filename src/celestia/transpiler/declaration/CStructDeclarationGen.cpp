#include "celestia/ir/IRIds.hpp"
#include "celestia/transpiler/CGenerator.hpp"

namespace celestia::codegen {

void CGenerator::generate_type(ir::TypeId id) {

  const auto &type = ir.get_type(id);

  switch (type.kind) {

  case ir::TypeKind::Int: out << "int"; break;

  case ir::TypeKind::String: out << "const char*"; break;

  case ir::TypeKind::Bool: out << "bool"; break;

  case ir::TypeKind::Struct: {
    const auto &struct_type = static_cast<const ir::StructType &>(type);

    out << "struct ";

    const auto &structure = ir.get_struct(struct_type.id);

    out << ir.get_string(structure.name);

    break;
  }

    // ...
  }
}

void CGenerator::generate_struct(ir::StructId id) {

  const auto &structure = ir.get_struct(id);

  out << "struct ";

  out << ir.get_string(structure.name);

  out << " {\n";

  for (const auto &field : structure.fields) {

    out << "    ";

    generate_type(field.type);

    out << " ";

    out << ir.get_string(field.name);

    out << ";\n";
  }

  out << "};\n";
}

} // namespace celestia::codegen