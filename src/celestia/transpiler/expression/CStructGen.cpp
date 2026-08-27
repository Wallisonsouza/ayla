#include "celestia/transpiler/CGenerator.hpp"
#include <iostream>

namespace celestia::codegen {

void CGenerator::generate_struct_literal(const ast::StructLiteralNode *literal) {

  if (!literal) return;

  if (!literal->type_id.is_valid()) {
    std::cerr << "[CGenerator] struct literal has no resolved type\n";
    return;
  }

  const auto &type = context.compiler.types.get(literal->type_id);

  if (type.kind != semantic::TypeKind::Struct) {
    std::cerr << "[CGenerator] struct literal type is not a struct\n";
    return;
  }

  auto &struct_type = static_cast<const semantic::StructType &>(type);

  auto *symbol = context.compiler.symbols.get(struct_type.symbol);

  if (!symbol) {
    std::cerr << "[CGenerator] struct symbol not found\n";
    return;
  }

  out << "{";

  bool first = true;

  for (auto *field : literal->fields) {

    if (!field || !field->name) continue;

    if (!first) out << ", ";

    first = false;

    out << "." << field->name->str << " = ";

    if (field->value) generate_expression(field->value);
  }

  out << "}";
}

} // namespace celestia::codegen