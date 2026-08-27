#include "celestia/ast/statements/ExpressionStatementNode.hpp"
#include "celestia/transpiler/CGenerator.hpp"

namespace celestia::codegen {

void CGenerator::generate_expression_statement(const ast::ExpressionStatement *statement) {

  if (!statement || !statement->expression) return;

  out << "    ";

  generate_expression(statement->expression);

  out << ";\n";
}

} // namespace celestia::codegen