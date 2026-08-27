#include "celestia/transpiler/CGenerator.hpp"
#include <iostream>

namespace celestia::codegen {

// ============================================================
// ARRAY LITERAL
// ============================================================

void CGenerator::generate_array_literal(const ast::ArrayLiteralNode *literal) {

  if (!literal) {

    std::cerr << "[CGenerator] null array literal\n";

    return;
  }

  if (!literal->type_id.is_valid()) {

    std::cerr << "[CGenerator] array has no resolved type\n";

    return;
  }

  const auto &base = context.compiler.types.get(literal->type_id);

  if (base.kind != semantic::TypeKind::GenericInstance) {

    std::cerr << "[CGenerator] array does not have "
                 "a generic instance type\n";

    return;
  }

  const auto &type = static_cast<const semantic::GenericInstanceType &>(base);

  // array<T> precisa ter exatamente um argumento.
  if (type.arguments.size() != 1) {

    std::cerr << "[CGenerator] invalid array type\n";

    return;
  }

  TypeId element_type = type.arguments[0];

  if (!element_type.is_valid()) {

    std::cerr << "[CGenerator] array has invalid "
                 "element TypeId\n";

    return;
  }

  // ----------------------------------------------------------
  // []
  // ----------------------------------------------------------

  if (literal->elements.empty()) {

    out << "ayla_array_make(sizeof(";

    generate_type(element_type);

    out << "))";

    return;
  }

  // ----------------------------------------------------------
  // [a, b, c]
  // ----------------------------------------------------------

  out << "ayla_array_from((";

  generate_type(element_type);

  out << "[]){";

  bool first = true;

  for (auto *element : literal->elements) {

    if (!element) continue;

    if (!first) out << ", ";

    first = false;

    generate_expression(element);
  }

  out << "}, ";

  out << literal->elements.size();

  out << ", sizeof(";

  generate_type(element_type);

  out << "))";
}

} // namespace celestia::codegen