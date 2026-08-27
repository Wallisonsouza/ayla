#include "celestia/transpiler/CGenerator.hpp"

namespace celestia::codegen {

void CGenerator::generate_block(const ast::BlockStatement *block) {

  if (!block) return;

  for (auto *statement : block->statements) {

    if (!statement) continue;

    generate_statement(statement);
  }
}

} // namespace celestia::codegen