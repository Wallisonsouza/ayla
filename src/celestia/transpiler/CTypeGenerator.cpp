#include "CGenerator.hpp"

#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/ast/types/ReferenceType.hpp"

namespace celestia::codegen {
void CGenerator::generate_type(const ast::TypeNode *type) {

  if (!type) return;

  switch (type->kind) {

  case ast::NodeKind::NamedType: generate_named_type(static_cast<const ast::NamedType *>(type)); return;

  case ast::NodeKind::ArrayType: out << "AylaArray"; return;

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

  if (name == "string") {
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


} // namespace celestia::codegen