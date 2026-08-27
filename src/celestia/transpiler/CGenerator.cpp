#include "CGenerator.hpp"

#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"

#include <string>

namespace celestia::codegen {

void CGenerator::generate_module(const ast::ModuleDeclaration *module) {
  if (!module) return;

  structs.clear();
  dependencies.clear();
  ordered_structs.clear();

  visiting.clear();
  visited.clear();

  generate_runtime();

  collect_structs(module);

  generate_forward_declarations();

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
  out << "#include \"lib/ayla_array.h\"\n";
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

  for (auto *composition : decl->compositions) {
    if (composition) collect_type_dependency(composition, deps);
  }

  for (auto *field : decl->fields) {
    if (field && field->type) collect_type_dependency(field->type, deps);
  }
}

// ============================================================
// TYPE DEPENDENCY
// ============================================================

void CGenerator::collect_type_dependency(const ast::TypeNode *type, std::vector<std::string> &deps) {
  if (!type) return;

  switch (type->kind) {

  case ast::NodeKind::NamedType: {
    auto *named = static_cast<const ast::NamedType *>(type);

    if (!named->name) return;

    const std::string name = named->name->str;

    if (structs.contains(name)) deps.push_back(name);

    return;
  }

  case ast::NodeKind::GenericType: {
    auto *generic = static_cast<const ast::GenericTypeNode *>(type);

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
// STRUCT LITERAL
// ============================================================



} // namespace celestia::codegen