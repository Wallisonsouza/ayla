#pragma once

#include "celestia/ast/declarations/FunctionDeclarationNode.hpp"
#include "runtime/value/ArrayValue.hpp"
#include "runtime/value/ObjectValue.hpp"
#include <functional>
#include <memory>
#include <string>
#include <variant>
#include <vector>

enum class ValueKind { Number, Boolean, String, Null, Void, NativeFunction };

struct NullValue {};
struct VoidValue {};

namespace parser::node {
struct FunctionDeclarationNode;
}

struct RuntimeScope;

struct UserFunction {
  celestia::ast::node::FunctionDeclarationNode *node;
  std::shared_ptr<RuntimeScope> captured_scope;

  UserFunction(celestia::ast::node::FunctionDeclarationNode *n, std::shared_ptr<RuntimeScope> scope) : node(n), captured_scope(scope) {}
};

struct Value {

  using NativeFunction = std::function<Value(const std::vector<Value> &)>;

  using Storage = std::variant<double, bool, std::string, NullValue, VoidValue, NativeFunction, UserFunction, ArrayValue, ObjectValue>;

  Storage data;

  static Value Number(double v) { return Value{v}; }
  static Value Boolean(bool b) { return Value{b}; }
  static Value String(std::string s) { return Value{std::move(s)}; }
  static Value Null() { return Value{NullValue{}}; }
  static Value Void() { return Value{VoidValue{}}; }
  static Value Native(NativeFunction fn) { return Value{std::move(fn)}; }
  static Value User(celestia::ast::node::FunctionDeclarationNode *node, std::shared_ptr<RuntimeScope> scope) { return Value{UserFunction(node, scope)}; }
  static Value Array(array elements) { return Value{.data = ArrayValue{elements}}; }
  static Value Object() { return Value{ObjectValue{}}; }

  double get_number() const { return std::get<double>(data); }

  bool get_boolean() const { return std::get<bool>(data); }

  const std::string &get_string() const { return std::get<std::string>(data); }

  const NativeFunction &get_native() const { return std::get<NativeFunction>(data); }

  UserFunction &get_user_function() { return std::get<UserFunction>(data); }

  std::string convert_to_string() const {

    if (std::holds_alternative<double>(data)) return std::to_string(std::get<double>(data));

    if (std::holds_alternative<bool>(data)) return std::get<bool>(data) ? "true" : "false";

    if (std::holds_alternative<std::string>(data)) return std::get<std::string>(data);

    if (std::holds_alternative<NativeFunction>(data)) return "<native function>";

    if (std::holds_alternative<ArrayValue>(data)) {
      const auto &arr = std::get<ArrayValue>(data).elements;
      std::string out = "[";
      for (size_t i = 0; i < arr.size(); ++i) {
        out += arr[i] ? arr[i]->convert_to_string() : "null";
        if (i + 1 < arr.size()) out += ", ";
      }
      out += "]";
      return out;
    }

    if (std::holds_alternative<ObjectValue>(data)) {
      const auto &obj = std::get<ObjectValue>(data).fields;

      std::string out = "{";
      size_t i = 0;

      for (const auto &[key, val] : obj) {
        out += key + ": ";
        out += val ? val->convert_to_string() : "null";

        if (++i < obj.size()) out += ", ";
      }

      out += "}";
      return out;
    }

    return "void";
  }

  bool as_bool() const {
    if (std::holds_alternative<ArrayValue>(data)) return !std::get<ArrayValue>(data).elements.empty();

    if (std::holds_alternative<bool>(data)) return std::get<bool>(data);

    if (std::holds_alternative<double>(data)) return std::get<double>(data) != 0.0;

    if (std::holds_alternative<std::string>(data)) return !std::get<std::string>(data).empty();

    if (std::holds_alternative<NullValue>(data)) return false;
    if (std::holds_alternative<VoidValue>(data)) return false;
    if (std::holds_alternative<NativeFunction>(data)) return true;

    return false;
  }

  std::shared_ptr<Value> get_property(const std::string &name) {
    auto &obj = std::get<ObjectValue>(data).fields;

    auto it = obj.find(name);
    if (it == obj.end()) throw std::runtime_error("Property not found: ");

    return it->second;
  }

  bool is_object() const { return std::holds_alternative<ObjectValue>(data); }

  ObjectValue &get_object_ref() { return std::get<ObjectValue>(data); }

  const ObjectValue &get_object() const { return std::get<ObjectValue>(data); }

  bool is_number() const { return std::holds_alternative<double>(data); }

  bool is_array() const { return std::holds_alternative<ArrayValue>(data); }

  const array &get_array() const { return std::get<ArrayValue>(data).elements; }

  array &get_array() { return std::get<ArrayValue>(data).elements; }

  bool is_user_function() const { return std::holds_alternative<UserFunction>(data); }
  bool is_native_function() const { return std::holds_alternative<NativeFunction>(data); }
};

struct ExecResult {
  enum class Type { Value, Return };

  Type type;
  std::shared_ptr<Value> value;

  static ExecResult make_value(std::shared_ptr<Value> v) { return {Type::Value, std::move(v)}; }

  static ExecResult make_return(std::shared_ptr<Value> v) { return {Type::Return, std::move(v)}; }

  bool is_return() const { return type == Type::Return; }
};
