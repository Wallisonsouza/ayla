#include "CGenerator.hpp"
#include "celestia/ast/statements/ExpressionStatementNode.hpp"

namespace celestia::codegen {

void CGenerator::generate_statement(const ast::Statement *item) {

  if (!item) return;

  switch (item->kind) {

  case ast::NodeKind::VariableDeclaration:
  case ast::NodeKind::FunctionDeclaration:
  case ast::NodeKind::StructDeclaration:
  case ast::NodeKind::CapabilityDeclaration:
  case ast::NodeKind::ImplementationDeclaration: generate_declaration(static_cast<const ast::Declaration *>(item)); return;
  case ast::NodeKind::ExpressionStatement: generate_expression_statement(static_cast<const ast::ExpressionStatement *>(item)); return;


  default: return;
  }
}
void CGenerator::generate_expression_statement(const ast::ExpressionStatement *statement) {

  if (!statement || !statement->expression) return;

  out << "    ";

  generate_expression(statement->expression);

  out << ";\n";
}

} // namespace celestia::codegen