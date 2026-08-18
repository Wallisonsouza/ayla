#include "CGenerator.hpp"
#include "celestia/ast/patterns/IdentifierPatternNode.hpp"

namespace celestia::codegen {

void CGenerator::generate_function_declaration(const ast::FunctionDeclaration *function) {

  if (!function || !function->name) return;

  const bool is_main = function->name->str == "main";

  // --------------------------------------------------
  // Return type
  // --------------------------------------------------

  if (is_main) {
    out << "int";
  } else if (function->return_type) {
    generate_type(function->return_type);
  } else {
    out << "void";
  }

  out << " " << function->name->str << "(";

  generate_parameters(function);

  out << ")";

  // --------------------------------------------------
  // Extern / declaration
  // --------------------------------------------------

  if (!function->body) {
    out << ";\n\n";
    return;
  }

  out << " {\n";

  generate_block(function->body);

  // main precisa terminar com return 0
  if (is_main) { out << "    return 0;\n"; }

  out << "}\n\n";
}

void CGenerator::generate_block(const ast::BlockStatement *block) {

  if (!block) return;

  for (auto *statement : block->statements) {

    if (!statement) continue;

    generate_statement(statement);
  }
}


void CGenerator::generate_pattern(const ast::PatternNode *pattern) {

  if (!pattern) return;

  switch (pattern->kind) {

  case ast::NodeKind::NamePattern: generate_name_pattern(static_cast<const ast::IdentifierPatternNode *>(pattern)); return;

  default: return;
  }
}

void CGenerator::generate_name_pattern(const ast::IdentifierPatternNode *pattern) {

  if (!pattern || !pattern->name) return;

  if (pattern->type_annotation) {
    generate_type(pattern->type_annotation);
    out << " ";
  } else {
    out << "void *";
  }

  out << pattern->name->str;
}

void CGenerator::generate_parameters(const ast::FunctionDeclaration *function) {

  if (!function) return;

  if (function->parameters.empty()) {
    out << "void";
    return;
  }

  bool first = true;

  for (auto *pattern : function->parameters) {

    if (!pattern) continue;

    if (!first) out << ", ";

    generate_pattern(pattern);

    first = false;
  }

  if (first) out << "void";
}

} // namespace celestia::codegen