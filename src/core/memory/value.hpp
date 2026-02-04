#pragma once
#include "core/memory/symbol.hpp"
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
  parser::node::FunctionDeclarationNode *node;
  RuntimeScope *captured_scope;

  UserFunction(parser::node::FunctionDeclarationNode *n, RuntimeScope *scope) : node(n), captured_scope(scope) {}
};

struct Value {

  using array = std::vector<std::shared_ptr<Value>>;
  using ObjectFields = std::unordered_map<SymbolId, std::shared_ptr<Value>>;

  struct ArrayValue {
    array elements;
  };

  struct ObjectValue {
    ObjectFields fields;

    void set(SymbolId id, std::shared_ptr<Value> value) { fields[id] = std::move(value); }

    std::shared_ptr<Value> get(SymbolId id) const {
      auto it = fields.find(id);
      if (it != fields.end()) return it->second;

      return nullptr;
    }

    std::shared_ptr<Value> get_or_throw(SymbolId id) const {
      auto it = fields.find(id);
      if (it == fields.end()) throw std::runtime_error("Object field not found");

      return it->second;
    }

    bool has(SymbolId id) const { return fields.find(id) != fields.end(); }

    void remove(SymbolId id) { fields.erase(id); }

    size_t size() const { return fields.size(); }
  };

  using NativeFunction = std::function<Value(const std::vector<Value> &)>;

  using Storage = std::variant<double, bool, std::string, NullValue, VoidValue, NativeFunction, UserFunction, ArrayValue, ObjectValue>;

  Storage data;

  static Value Number(double v) { return Value{v}; }
  static Value Boolean(bool b) { return Value{b}; }
  static Value String(std::string s) { return Value{std::move(s)}; }
  static Value Null() { return Value{NullValue{}}; }
  static Value Void() { return Value{VoidValue{}}; }
  static Value Native(NativeFunction fn) { return Value{std::move(fn)}; }
  static Value User(parser::node::FunctionDeclarationNode *node, RuntimeScope *scope) { return Value{UserFunction(node, scope)}; }
  static Value Array(array elements) { return Value{.data = ArrayValue{elements}}; }
  static Value Object(ObjectFields fields) { return Value{ObjectValue{std::move(fields)}}; }

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

  std::shared_ptr<Value> get_property(const SymbolId &name) {
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
