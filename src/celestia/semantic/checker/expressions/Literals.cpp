#include "celestia/semantic/checker/TypeChecker.hpp"
#include "celestia/semantic/types/BuiltinTypes.hpp"

namespace celestia::semantic {

void TypeChecker::number_literal(ast::NumberLiteralNode *node) {

  if (!node) return;

  node->resolved_type = &NumberType;
}

void TypeChecker::string_literal(ast::StringLiteralNode *node) {

  if (!node) return;

  node->resolved_type = &StringType;
}

void TypeChecker::boolean_literal(ast::BoolLiteralNode *node) {

  if (!node) return;

  node->resolved_type = &BooleanType;
}



} // namespace celestia::semantic