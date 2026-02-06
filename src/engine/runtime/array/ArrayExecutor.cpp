#include "engine/runtime/array/ArrayValue.hpp"
#include "engine/runtime/executor.hpp"

ExecResult Executor::execute_array(CompilationUnit &unit, ayla::ast::node::ArrayLiteralNode *node) {

  array elements;

  for (auto *el : node->elements) {
    auto v = execute_node(unit, el);
    if (v.is_return()) return v;
    elements.push_back(v.value);
  }

  return ExecResult::make_value(std::make_shared<Value>(Value::Array(std::move(elements))));
}

ExecResult Executor::execute_index_access(CompilationUnit &unit, ayla::ast::node::IndexAccessNode *node) {
  auto base = execute_node(unit, node->base).value;
  auto index = execute_node(unit, node->index).value;

  if (!base->is_array()) throw std::runtime_error("Index access on non-array");

  size_t i = static_cast<size_t>(index->get_number());
  auto &arr = base->get_array();

  if (i >= arr.size()) return ExecResult::make_value(std::make_shared<Value>(Value::Null()));

  return ExecResult::make_value(arr[i]);
}