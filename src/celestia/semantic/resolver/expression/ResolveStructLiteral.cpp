#include "celestia/semantic/resolver/Resolver.hpp"
#include <iostream>

namespace celestia::semantic {

void Resolver::struct_literal(ast::StructLiteralNode *node) {

  if (!node) return;

  if (!node->type) {
    std::cerr << "[Resolver] struct literal has no type\n";
    return;
  }

  resolve(node->type);

  if (!node->type->symbol_id.is_valid()) {
    std::cerr << "[Resolver] struct literal type has no symbol\n";
    return;
  }

  node->symbol_id = node->type->symbol_id;

  for (auto *field : node->fields) {

    if (!field) continue;

    if (field->value) resolve(field->value);
  }
}
} // namespace celestia::semantic