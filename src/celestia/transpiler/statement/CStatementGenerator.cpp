#include "celestia/ast/statements/ExpressionStatementNode.hpp"
#include "celestia/transpiler/CGenerator.hpp"

namespace celestia::codegen {

void CGenerator::generate_statement(const ast::Statement *item) {

  if (!item) return;

  switch (item->kind) {

  case ast::NodeKind::ReturnStatement: generate_return_statement(static_cast<const ast::ReturnStatement *>(item)); return;
  case ast::NodeKind::VariableDeclaration:
  case ast::NodeKind::FunctionDeclaration:
  case ast::NodeKind::StructDeclaration:
  case ast::NodeKind::CapabilityDeclaration:

  case ast::NodeKind::ImplementationDeclaration: generate_declaration(static_cast<const ast::Declaration *>(item)); return;
  case ast::NodeKind::ExpressionStatement: generate_expression_statement(static_cast<const ast::ExpressionStatement *>(item)); return;

  default: return;
  }
}

} // namespace celestia::codegen