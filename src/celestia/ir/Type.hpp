#pragma once

#include <utility>
#include <vector>

#include "celestia/ir/IRIds.hpp"
#include "celestia/ir/TypeKind.hpp"

namespace celestia::ir {

struct Type {

  TypeKind kind;

  explicit Type(TypeKind kind) : kind(kind) {}

  virtual ~Type() = default;
};

struct ArrayType : Type {

  TypeId element_type;

  explicit ArrayType(TypeId element_type) : Type(TypeKind::Array), element_type(element_type) {}
};

struct PointerType : Type {

  TypeId pointee;

  explicit PointerType(TypeId pointee) : Type(TypeKind::Pointer), pointee(pointee) {}
};

struct StructType : Type {

  StructId id;

  explicit StructType(StructId id) : Type(TypeKind::Struct), id(id) {}
};

struct InterfaceType : Type {

  InterfaceId id;

  explicit InterfaceType(InterfaceId id) : Type(TypeKind::Interface), id(id) {}
};

struct FunctionType : Type {

  std::vector<TypeId> parameters;
  TypeId return_type;

  FunctionType(std::vector<TypeId> parameters, TypeId return_type) : Type(TypeKind::Function), parameters(std::move(parameters)), return_type(return_type) {}
};

} // namespace celestia::ir