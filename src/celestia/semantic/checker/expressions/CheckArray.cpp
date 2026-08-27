#include "celestia/semantic/checker/TypeChecker.hpp"

namespace celestia::semantic {

void TypeChecker::array_literal(ast::ArrayLiteralNode *node) {

  // if (!node) return;

  // if (node->elements.empty()) {
  //   error(node, "cannot infer type of empty array");
  //   return;
  // }

  // // ------------------------------------------------
  // // Primeiro elemento
  // // ------------------------------------------------

  // check(node->elements[0]);

  // TypeId element_type = node->elements[0]->type_id;

  // if (!element_type.is_valid()) {
  //   error(node->elements[0], "array element has no valid type");

  //   return;
  // }

  // // ------------------------------------------------
  // // Demais elementos
  // // ------------------------------------------------

  // for (size_t i = 1; i < node->elements.size(); ++i) {

  //   check(node->elements[i]);

  //   TypeId type = node->elements[i]->type_id;

  //   if (!type.is_valid()) {

  //     error(node->elements[i], "array element has no valid type");

  //     return;
  //   }

  //   if (!is_assignable(element_type, type)) {

  //     error(node->elements[i], "array elements must have the same type");

  //     return;
  //   }
  // }

  // // ------------------------------------------------
  // // Array<T>
  // // ------------------------------------------------

  // TypeId array_type = context.compiler.types.get_or_create_generic(context.compiler.builtins.array_symbol, {element_type});

  // if (!array_type.is_valid()) {

  //   error(node, "could not create array type");

  //   return;
  // }

  // node->type_id = array_type;

  // std::cout << "[TypeChecker] array type = " << context.compiler.types.get(array_type).to_string() << '\n';
}

} // namespace celestia::semantic