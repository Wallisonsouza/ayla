
#include "engine/runtime/executor.hpp"

ExecResult Executor::execute_object(CompilationUnit &unit, parser::node::ObjectLiteralNode *node) {

  auto obj_val = std::make_shared<Value>(Value::Object());

  auto &obj = obj_val->get_object_ref();

  for (auto &field : node->field_list->elements) {
    auto result = execute_node(unit, field->value);
    obj.set(field->key->resolved_symbol_id, result.value);
  }

  return ExecResult::make_value(obj_val);
}

ExecResult Executor::execute_member_acess(CompilationUnit &unit, ayla::ast::node::MemberAccessExpressionNode *member) {

  //
  auto base_val = execute_node(unit, member->base).value;

  return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
}
