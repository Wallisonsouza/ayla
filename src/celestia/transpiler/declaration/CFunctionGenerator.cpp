#include "celestia/transpiler/CGenerator.hpp"

#include <iostream>

namespace celestia::codegen {

void CGenerator::generate_function_declaration(const ast::FunctionDeclaration *function) {

  if (!function || !function->name) return;

  // ------------------------------------------------
  // FunctionType
  // ------------------------------------------------

  if (!function->type_id.is_valid()) {

    std::cerr << "[CGenerator] function has no resolved type\n";

    return;
  }

  const auto &base_type = context.compiler.types.get(function->type_id);

  if (base_type.kind != semantic::TypeKind::Function) {

    std::cerr << "[CGenerator] declaration is not a function type\n";

    return;
  }

  const auto &function_type = static_cast<const semantic::FunctionType &>(base_type);

  const bool is_main = function->name->str == "main";

  // ------------------------------------------------
  // Return type
  // ------------------------------------------------

  if (is_main) {

    // main em C
    out << "int";

  } else {

    generate_type(function_type.return_type);
  }

  // ------------------------------------------------
  // Nome + parâmetros
  // ------------------------------------------------

  out << " " << function->name->str << "(";

  generate_parameters(function_type, function);

  out << ")";

  // ------------------------------------------------
  // Declaration
  // ------------------------------------------------

  if (!function->body) {

    out << ";\n\n";

    return;
  }

  // ------------------------------------------------
  // Body
  // ------------------------------------------------

  out << " {\n";

  generate_block(function->body);

  if (is_main) out << "    return 0;\n";

  out << "}\n\n";
}

// ============================================================
// PARAMETERS
// ============================================================

void CGenerator::generate_parameters(const semantic::FunctionType &type, const ast::FunctionDeclaration *function) {

  if (!function) return;

  if (type.params.empty()) {

    out << "void";

    return;
  }

  bool first = true;

  for (size_t i = 0; i < type.params.size(); ++i) {

    if (!first) out << ", ";

    // ------------------------------------------------
    // Tipo
    // ------------------------------------------------

    generate_type(type.params[i]);

    out << " ";

    // ------------------------------------------------
    // Nome
    // ------------------------------------------------

    if (i < function->parameters.size()) {

      auto *pattern = static_cast<const ast::NamedPattern *>(function->parameters[i]);

      if (pattern && pattern->name) out << pattern->name->str;
    }

    first = false;
  }
}

} // namespace celestia::codegen