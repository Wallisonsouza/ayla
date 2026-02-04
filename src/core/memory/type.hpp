#pragma once

#include "core/memory/symbol.hpp"
#include <string>
#include <unordered_map>
#include <vector>

enum class TypeKind { Unknown, Number, String, Boolean, Function, Object, Array, Void };

struct Type {
  TypeKind kind;

  explicit Type(TypeKind k) : kind(k) {}
  virtual ~Type() = default;
};

struct ObjectType : Type {
  std::unordered_map<std::string, Type *> members;

  ObjectType() : Type(TypeKind::Object) {}

  bool has_member(const std::string &name) const { return members.find(name) != members.end(); }

  Type *get_member(const std::string &name) const {
    auto it = members.find(name);
    return (it == members.end()) ? nullptr : it->second;
  }

  void add_member(const std::string &name, Type *type) { members[name] = type; }
};

struct ModuleType : ObjectType {};

struct FunctionType : Type {
  std::vector<Type *> params;
  Type *return_type = nullptr;

  FunctionType() : Type(TypeKind::Function) {}
};

struct ArrayType : Type {
  Type *element_type;

  ArrayType(Type *el) : Type(TypeKind::Array), element_type(el) {}
};
