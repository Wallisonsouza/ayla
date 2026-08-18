#include "CGenerator.hpp"

#include "celestia/ast/types/Array.hpp"
#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/ast/types/ReferenceType.hpp"

namespace celestia::codegen {
void CGenerator::generate_type(const ast::TypeNode *type) {

  if (!type) return;

  switch (type->kind) {

  case ast::NodeKind::NamedType: generate_named_type(static_cast<const ast::NamedType *>(type)); return;

  case ast::NodeKind::ArrayType: generate_array_type_name(static_cast<const ast::ArrayType *>(type)); return;

  case ast::NodeKind::ReferenceType: generate_reference_type(static_cast<const ast::ReferenceType *>(type)); return;

  case ast::NodeKind::GenericType: generate_generic_type(static_cast<const ast::GenericType *>(type)); return;

  default: return;
  }
}

// ============================================================
// NAMED TYPE
// ============================================================

void CGenerator::generate_named_type(const ast::NamedType *type) {

  if (!type || !type->name) return;

  const std::string &name = type->name->str;

  if (name == "Int") {
    out << "int";
    return;
  }

  if (name == "Number") {
    out << "float";
    return;
  }

  if (name == "String") {
    out << "const char *";
    return;
  }

  if (name == "Bool") {
    out << "bool";
    return;
  }

  if (name == "Float") {
    out << "double";
    return;
  }

  if (name == "Char") {
    out << "char";
    return;
  }

  if (name == "Void") {
    out << "void";
    return;
  }

  // Tipo definido pelo usuário.
  out << name;
}

// ============================================================
// ARRAY TYPE NAME
// ============================================================

void CGenerator::generate_array_type_name(const ast::ArrayType *type) {

  if (!type) return;

  out << array_name(type);
}

// ============================================================
// REFERENCE TYPE
// ============================================================

void CGenerator::generate_reference_type(const ast::ReferenceType *type) {

  if (!type || !type->target) return;

  generate_type(type->target);

  out << " *";
}

// ============================================================
// GENERIC TYPE
// ============================================================

void CGenerator::generate_generic_type(const ast::GenericType *type) {

  if (!type || !type->name) return;

  // Futuramente.
  out << type->name->str;
}

// ============================================================
// ARRAY NAME
// ============================================================

std::string CGenerator::array_name(const ast::TypeNode *type) const {

  if (!type) return {};

  // Array<T>
  if (type->kind == ast::NodeKind::ArrayType) {

    auto *array = static_cast<const ast::ArrayType *>(type);

    if (!array->element_type) return "AylaArray";

    return "Array_" + array_name(array->element_type);
  }

  // ref<T>
  if (type->kind == ast::NodeKind::ReferenceType) {

    auto *reference = static_cast<const ast::ReferenceType *>(type);

    if (!reference->target) return "Ref";

    return "Ref_" + array_name(reference->target);
  }

  // Tipo normal.
  if (type->kind == ast::NodeKind::NamedType) {

    auto *named = static_cast<const ast::NamedType *>(type);

    if (!named->name) return "Unknown";

    return named->name->str;
  }

  // Generic.
  if (type->kind == ast::NodeKind::GenericType) {

    auto *generic = static_cast<const ast::GenericType *>(type);

    if (!generic->name) return "Generic";

    return generic->name->str;
  }

  return "Unknown";
}

} // namespace celestia::codegen