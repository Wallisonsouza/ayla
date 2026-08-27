#include "celestia/semantic/checker/TypeChecker.hpp"

namespace celestia::semantic {
void TypeChecker::binary_expression(ast::BinaryExpressionNode *node) {

  check(node->lhs);
  check(node->rhs);

  auto *left_type = node->lhs->type;
  auto *right_type = node->rhs->type;

  if (!left_type || !right_type) return;

  if (left_type != right_type) {
    error(node, "binary expression requires operands of the same type");
    return;
  }

  node->type = left_type;
}
} // namespace celestia::semantic