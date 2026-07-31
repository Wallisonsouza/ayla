#pragma once

#include "celestia/semantic/types/PrimitiveType.hpp"
#include "celestia/semantic/types/TypeKind.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace celestia::semantic {

struct Type {

  TypeKind kind;

  explicit Type(TypeKind kind) : kind(kind) {}

  virtual ~Type() = default;

  virtual std::string to_string() const {
    switch (kind) {
    case TypeKind::Unknown: return "Unknown";

    case TypeKind::Primitive: return "Primitive";

    case TypeKind::Function: return "Function";

    case TypeKind::Object: return "Object";

    case TypeKind::Array: return "Array";
    }

    return "Invalid";
  }
};

struct PrimitiveTypeInfo : Type {

  PrimitiveType primitive;

  PrimitiveTypeInfo(PrimitiveType primitive) : Type(TypeKind::Primitive), primitive(primitive) {}

  std::string to_string() const override {
    switch (primitive) {
    case PrimitiveType::Number: return "Number";

    case PrimitiveType::String: return "String";

    case PrimitiveType::Boolean: return "Boolean";

    case PrimitiveType::Void: return "Void";
    }

    return "Unknown";
  }
};

struct ObjectType : Type {
  std::unordered_map<std::string, Type *> members;

  ObjectType() : Type(TypeKind::Object) {}

  bool has_member(const std::string &name) const { return members.find(name) != members.end(); }

  Type *get_member(const std::string &name) const {
    auto it = members.find(name);
    return it == members.end() ? nullptr : it->second;
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

} // namespace celestia::semantic
