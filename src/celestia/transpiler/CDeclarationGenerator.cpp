#include "CGenerator.hpp"
#include "celestia/ast/declarations/ImplementationDeclaration.hpp"
#include "celestia/ast/types/NamedType.hpp"

namespace celestia::codegen {

void CGenerator::generate_declaration(const ast::Declaration *declaration) {
  if (!declaration) return;

  switch (declaration->kind) {

  case ast::NodeKind::VariableDeclaration: generate_variable_declaration(static_cast<const ast::VariableDeclaration *>(declaration)); return;

  case ast::NodeKind::FunctionDeclaration: generate_function_declaration(static_cast<const ast::FunctionDeclaration *>(declaration)); return;

  case ast::NodeKind::StructDeclaration: generate_struct_declaration(static_cast<const ast::StructDeclaration *>(declaration)); return;

  case ast::NodeKind::CapabilityDeclaration: generate_capability_declaration(static_cast<const ast::CapabilityDeclaration *>(declaration)); return;

  case ast::NodeKind::ImplementationDeclaration: generate_impl_declaration(static_cast<const ast::ImplDeclaration *>(declaration)); return;

  default: return;
  }
}

void CGenerator::generate_capability_declaration(const ast::CapabilityDeclaration *declaration) {

  if (!declaration || !declaration->name) return;

  const std::string capability_name = declaration->name->str;

  for (const auto *function : declaration->members) {

    if (!function || !function->name) continue;

    if (!function->body) continue;

    out << "static ";

    generate_type(function->return_type);

    out << " " << capability_name << "_" << function->name->str << "(void *self";

    for (const auto *parameter : function->parameters) {

      if (!parameter) continue;

      out << ", ";
      generate_pattern(parameter);
    }

    out << ")";

    generate_block(function->body);

    out << "\n\n";
  }

  out << "typedef struct {\n";

  for (const auto *function : declaration->members) {

    if (!function || !function->name) continue;

    out << "    ";

    generate_type(function->return_type);

    out << " (*" << function->name->str << ")(void *self";

    for (const auto *parameter : function->parameters) {

      if (!parameter) continue;

      out << ", ";
      generate_pattern(parameter);
    }

    out << ");\n";
  }

  out << "} " << capability_name << ";\n\n";
}

void CGenerator::generate_impl_declaration(const ast::ImplDeclaration *declaration) {

  if (!declaration) return;

  auto *target = declaration->target;
  auto *capability = declaration->capability;

  if (!target || !capability) return;

  auto *target_type = static_cast<const ast::NamedType *>(target);

  auto *capability_type = static_cast<const ast::NamedType *>(capability);

  if (!target_type->name || !capability_type->name) return;

  const std::string target_name = target_type->name->str;

  const std::string capability_name = capability_type->name->str;

  for (const auto *function : declaration->members) {

    if (!function || !function->name) continue;

    out << "static ";

    // Retorno
    generate_type(function->return_type);

    out << " " << target_name << "_" << function->name->str << "(";

    // self genérico da capability
    out << "void *self";

    // Parâmetros
    for (const auto *parameter : function->parameters) {

      if (!parameter) continue;

      out << ", ";
      generate_pattern(parameter);
    }

    out << ");\n";
  }

  out << "\n";

  // ==================================================
  // 2. Tabela da capability
  // ==================================================

  out << "static " << capability_name << " " << target_name << "_" << capability_name << " = {\n";

  for (const auto *function : declaration->members) {

    if (!function || !function->name) continue;

    out << "    ." << function->name->str << " = " << target_name << "_" << function->name->str << ",\n";
  }

  out << "};\n\n";
}

} // namespace celestia::codegen