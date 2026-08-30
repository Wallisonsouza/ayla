#include "celestia/semantic/checker/TypeChecker.hpp"

namespace celestia::semantic {

void TypeChecker::binary_expression(ast::BinaryExpressionNode *node) {

  if (!node || !node->lhs || !node->rhs) return;

  check(node->lhs);
  check(node->rhs);

  TypeId lhs_type = node->lhs->type_id;
  TypeId rhs_type = node->rhs->type_id;

  if (!is_same_type(lhs_type, rhs_type)) {

    error(node, "binary expression requires operands of the same type");

    return;
  }

  node->type_id = lhs_type;
}
} // namespace celestia::semantic