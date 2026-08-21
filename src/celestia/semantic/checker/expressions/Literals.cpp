#include "celestia/semantic/checker/TypeChecker.hpp"
#include "celestia/semantic/types/BuiltinTypes.hpp"

namespace celestia::semantic {

void TypeChecker::number_literal(ast::NumberLiteralNode *node) { node->resolved_type = &NumberType; }

void TypeChecker::string_literal(ast::StringLiteralNode *node) { node->resolved_type = &StringType; }

void TypeChecker::boolean_literal(ast::BoolLiteralNode *node) { node->resolved_type = &BooleanType; }


} // namespace celestia::semantic