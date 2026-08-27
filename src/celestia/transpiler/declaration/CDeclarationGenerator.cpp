#include "celestia/transpiler/CGenerator.hpp"

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
} // namespace celestia::codegen