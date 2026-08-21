#include "celestia/semantic/checker/TypeChecker.hpp"
#include "celestia/semantic/types/BuiltinTypes.hpp"

namespace celestia::semantic {

void TypeChecker::array_literal(ast::ArrayLiteralNode *node) {

  if (node->elements.empty()) {
    error(node, "cannot infer type of empty array");
    return;
  }

  check(node->elements[0]);

  auto *element_type = node->elements[0]->resolved_type;

  if (!element_type) return;

  for (size_t i = 1; i < node->elements.size(); ++i) {

    check(node->elements[i]);

    auto *type = node->elements[i]->resolved_type;

    if (!type) return;

    if (type != element_type) {
      error(node->elements[i], "array elements must have the same type");
      return;
    }
  }

  node->resolved_type = context.unit.types.alloc<ArrayType>(element_type);
}

} // namespace celestia::semantic