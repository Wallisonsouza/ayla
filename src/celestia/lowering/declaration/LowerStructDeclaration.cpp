#include "celestia/ast/NodeCast.hpp"
#include "celestia/lowering/Lowering.hpp"

namespace celestia::lowering {
void LoweringContext::lower_struct_declaration(const ast::StructDeclaration *node) {

  if (!node || !node->name) return;

  ir::StringId name = ir.intern_string(node->name->str);

  ir::StructId struct_id = ir.create_struct(name);

  for (const auto *field : node->fields) {

    if (!field || !field->type) continue;

    ir::TypeId field_type = lower_type(field->type->type_id);

    if (!field_type.is_valid()) continue;

    ir::StringId field_name = ir.intern_string(field->name->str);

    ir.add_struct_field(struct_id, field_name, field_type);
  }

  ir.get_or_create_struct_type(struct_id);
}

} // namespace celestia::lowering