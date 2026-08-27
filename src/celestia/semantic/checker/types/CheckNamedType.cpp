#include "celestia/semantic/checker/TypeChecker.hpp"

namespace celestia::semantic {

TypeId TypeChecker::check_named_type(ast::NamedType *node) {

  if (!node) return TypeId::invalid();

  auto *symbol = context.compiler.symbols.get(node->symbol_id);

  if (!symbol) {
    error(node, "named type symbol not found");
    return TypeId::invalid();
  }

  if (!symbol->type.is_valid()) {
    error(node, "symbol has no valid type");
    return TypeId::invalid();
  }

  node->type_id = symbol->type;

  return symbol->type;
}

} // namespace celestia::semantic