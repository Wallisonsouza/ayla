#include "runtime/interpreter/executor.hpp"

ExecResult Executor::execute_object(CompilationUnit &unit, ayla::ast::node::ObjectLiteralNode *node) {

  auto obj_val = std::make_shared<Value>(Value::Object());

  auto &obj = obj_val->get_object_ref();

  for (auto &field : node->fields) {
    auto result = execute_node(unit, field->value);

    auto symbol = unit.context.symbol_manager.get(field->key->resolved_symbol_id);
    obj.set(symbol->name, result.value);
  }

  return ExecResult::make_value(obj_val);
}

ExecResult Executor::execute_member_acess(CompilationUnit &unit, ayla::ast::node::MemberAccessExpressionNode *member) {

  auto base_res = execute_node(unit, member->base);
  auto base_val = base_res.value;

  if (!base_val || !base_val->is_object()) { throw std::runtime_error("Invalid member access on non-object"); }

  auto &obj = base_val->get_object_ref();

  const std::string &field_name = member->field->name;

  if (!obj.has(field_name)) { throw std::runtime_error("Field not found: " + field_name); }

  return ExecResult::make_value(obj.get(field_name));
}
