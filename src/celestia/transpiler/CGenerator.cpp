#include "CGenerator.hpp"

#include "celestia/ast/types/Array.hpp"
#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/ast/types/ReferenceType.hpp"

#include <string>

namespace celestia::codegen {

// ============================================================
// MODULE
// ============================================================

void CGenerator::generate_module(const ast::ModuleDeclaration *module) {

  if (!module) return;

  structs.clear();
  dependencies.clear();
  ordered_structs.clear();

  visiting.clear();
  visited.clear();

  array_types.clear();
  generated_arrays.clear();

  generate_runtime();

  // Primeiro conhecemos todos os structs.
  collect_structs(module);

  // Depois descobrimos todos os arrays utilizados.
  collect_array_types(module);

  // Forward declarations dos structs.
  generate_forward_declarations();

  // Gera os tipos de array completos.
  generate_array_types();

  // Ordenação por dependências.
  for (const auto &[name, decl] : structs) {
    (void)decl;
    visit_struct(name);
  }

  for (auto *decl : module->declarations) { generate_declaration(decl); }
}

// ============================================================
// RUNTIME
// ============================================================

void CGenerator::generate_runtime() {

  out << "#include <stddef.h>\n";
  out << "#include <stdbool.h>\n";
  out << "\n";
}

// ============================================================
// STRUCT COLLECTION
// ============================================================

void CGenerator::collect_structs(const ast::ModuleDeclaration *module) {

  if (!module) return;

  for (auto *decl : module->declarations) {

    if (!decl) continue;

    if (decl->kind != ast::NodeKind::StructDeclaration) continue;

    auto *struct_decl = static_cast<const ast::StructDeclaration *>(decl);

    if (!struct_decl->name) continue;

    const std::string name = struct_decl->name->str;

    structs.emplace(name, struct_decl);
  }

  for (const auto &[name, decl] : structs) {

    (void)name;

    collect_struct_dependencies(decl);
  }
}

// ============================================================
// STRUCT DEPENDENCIES
// ============================================================

void CGenerator::collect_struct_dependencies(const ast::StructDeclaration *decl) {

  if (!decl || !decl->name) return;

  const std::string name = decl->name->str;

  auto &deps = dependencies[name];

  // ----------------------------------------------------------
  // Compositions
  // ----------------------------------------------------------

  for (auto *composition : decl->compositions) {

    if (!composition) continue;

    collect_type_dependency(composition, deps);
  }

  // ----------------------------------------------------------
  // Fields
  // ----------------------------------------------------------

  for (auto *field : decl->fields) {

    if (!field || !field->type) continue;

    collect_type_dependency(field->type, deps);
  }
}

// ============================================================
// TYPE DEPENDENCY
// ============================================================

void CGenerator::collect_type_dependency(const ast::TypeNode *type, std::vector<std::string> &deps) {

  if (!type) return;

  switch (type->kind) {

    // ----------------------------------------------------------
    // NamedType
    // ----------------------------------------------------------

  case ast::NodeKind::NamedType: {

    auto *named = static_cast<const ast::NamedType *>(type);

    if (!named->name) return;

    const std::string name = named->name->str;

    if (structs.contains(name)) deps.push_back(name);

    return;
  }

    // ----------------------------------------------------------
    // ReferenceType
    // ----------------------------------------------------------

  case ast::NodeKind::ReferenceType: {

    auto *reference = static_cast<const ast::ReferenceType *>(type);

    collect_type_dependency(reference->target, deps);

    return;
  }

    // ----------------------------------------------------------
    // ArrayType
    // ----------------------------------------------------------

  case ast::NodeKind::ArrayType: {

    auto *array = static_cast<const ast::ArrayType *>(type);

    collect_type_dependency(array->element_type, deps);

    return;
  }

    // ----------------------------------------------------------
    // GenericType
    // ----------------------------------------------------------

  case ast::NodeKind::GenericType: {

    auto *generic = static_cast<const ast::GenericType *>(type);

    for (auto *argument : generic->arguments) { collect_type_dependency(argument, deps); }

    return;
  }

  default: return;
  }
}

// ============================================================
// FORWARD DECLARATIONS
// ============================================================

void CGenerator::generate_forward_declarations() {

  for (const auto &[name, decl] : structs) {

    (void)decl;

    out << "typedef struct " << name << " " << name << ";\n";
  }

  out << "\n";
}

// ============================================================
// STRUCT ORDER
// ============================================================

void CGenerator::visit_struct(const std::string &name) {

  if (visited.contains(name)) return;

  if (visiting.contains(name)) return;

  auto it = structs.find(name);

  if (it == structs.end()) return;

  visiting.insert(name);

  auto dep_it = dependencies.find(name);

  if (dep_it != dependencies.end()) {

    for (const auto &dependency : dep_it->second) { visit_struct(dependency); }
  }

  visiting.erase(name);

  visited.insert(name);

  ordered_structs.push_back(it->second);
}

// ============================================================
// STRUCT DECLARATION
// ============================================================

void CGenerator::generate_struct_declaration(const ast::StructDeclaration *decl) {

  if (!decl || !decl->name) return;

  out << "struct " << decl->name->str << " {\n";

  // ----------------------------------------------------------
  // Compositions
  // ----------------------------------------------------------

  for (auto *composition : decl->compositions) {

    if (!composition) continue;

    out << "    ";

    generate_type(composition);

    out << " base;\n";
  }

  // ----------------------------------------------------------
  // Fields
  // ----------------------------------------------------------

  for (auto *field : decl->fields) {

    if (!field) continue;

    generate_field(field);
  }

  out << "};\n\n";
}

// ============================================================
// FIELD
// ============================================================

void CGenerator::generate_field(const ast::FieldDeclaration *field) {

  if (!field || !field->name || !field->type) return;

  out << "    ";

  // O tipo já sabe se é valor, array ou referência.
  generate_type(field->type);

  out << " " << field->name->str << ";\n";
}

// ============================================================
// ARRAY COLLECTION
// ============================================================

void CGenerator::collect_array_types(const ast::ModuleDeclaration *module) {

  if (!module) return;

  for (auto *decl : module->declarations) {

    if (!decl) continue;

    if (decl->kind != ast::NodeKind::StructDeclaration) continue;

    auto *struct_decl = static_cast<const ast::StructDeclaration *>(decl);

    for (auto *field : struct_decl->fields) {

      if (!field) continue;

      collect_array_type(field->type);
    }
  }
}

// ============================================================
// COLLECT ARRAY TYPE
// ============================================================

void CGenerator::collect_array_type(const ast::TypeNode *type) {

  if (!type) return;

  // ref<[T]>
  if (type->kind == ast::NodeKind::ReferenceType) {

    auto *reference = static_cast<const ast::ReferenceType *>(type);

    collect_array_type(reference->target);

    return;
  }

  if (type->kind != ast::NodeKind::ArrayType) return;

  auto *array = static_cast<const ast::ArrayType *>(type);

  if (!array->element_type) return;

  // Primeiro arrays internos.
  collect_array_type(array->element_type);

  const std::string name = array_name(array);

  array_types.emplace(name, array);
}

// ============================================================
// ARRAY GENERATION
// ============================================================

void CGenerator::generate_array_types() {

  for (const auto &[name, type] : array_types) {

    (void)name;

    generate_array_type(type);
  }
}

// ============================================================
// ARRAY TYPE
// ============================================================
//
// Aqui generate_array_type realmente gera o tipo C completo:
//
// typedef struct Array_Int {
//     int *data;
//     size_t size;
//     size_t capacity;
// } Array_Int;
//
void CGenerator::generate_array_type(const ast::ArrayType *type) {

  if (!type || !type->element_type) return;

  const std::string name = array_name(type);

  if (!generated_arrays.insert(name).second) return;

  // Array aninhado.
  if (type->element_type->kind == ast::NodeKind::ArrayType) {

    auto *inner = static_cast<const ast::ArrayType *>(type->element_type);

    generate_array_type(inner);
  }

  out << "typedef struct " << name << " {\n";

  out << "    ";

  generate_array_element_name(type->element_type);

  out << " *data;\n";

  out << "    size_t size;\n";
  out << "    size_t capacity;\n";

  out << "} " << name << ";\n\n";
}

// ============================================================
// ARRAY ELEMENT TYPE
// ============================================================
//
// [Int]         -> int *data
// [Point]       -> Point *data
// [ref<Point>]  -> Point **data
// [[Int]]       -> Array_Int *data
//
void CGenerator::generate_array_element_name(const ast::TypeNode *type) {

  if (!type) return;

  generate_type(type);
}

// ============================================================
// TYPE
// ============================================================


// ============================================================
// STRUCT LITERAL
// ============================================================

void CGenerator::generate_struct_literal(const ast::StructLiteralNode *node) {

  if (!node || !node->type) return;

  out << "(";

  generate_type(node->type);

  out << "){";

  bool first = true;

  for (auto *field : node->fields) {

    if (!field) continue;

    if (!first) out << ", ";

    first = false;

    out << ".";

    if (field->name) out << field->name->str;

    out << " = ";

    if (field->value) generate_expression(field->value);
  }

  out << "}";
}

} // namespace celestia::codegen