#include "celestia/lowering/Lowering.hpp"

namespace celestia::lowering {

ir::ValueId LoweringContext::lower_number_literal(const ast::NumberLiteralNode *node) {

  if (!node) return ir::ValueId::invalid();

  ir::TypeId type = lower_type(node->type_id);

  if (!type.is_valid()) return ir::ValueId::invalid();

  return ir.create_constant(type, node->value);
}

ir::ValueId LoweringContext::lower_string_literal(const ast::StringLiteralNode *node) {

  if (!node) return ir::ValueId::invalid();

  ir::TypeId type = lower_type(node->type_id);

  if (!type.is_valid()) return ir::ValueId::invalid();

  return ir.create_constant(type, node->value);
}

ir::ValueId LoweringContext::lower_bool_literal(const ast::BoolLiteralNode *node) {

  if (!node) return ir::ValueId::invalid();

  ir::TypeId type = lower_type(node->type_id);

  if (!type.is_valid()) return ir::ValueId::invalid();

  return ir.create_constant(type, node->value);
}

} // namespace celestia::lowering