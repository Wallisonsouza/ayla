#pragma once

#include "celestia/core/ids/Ids.hpp"
#include "celestia/core/memory/Arena.hpp"
#include "celestia/semantic/types/type.hpp"

#include <unordered_map>
#include <vector>

class TypeManager {
public:
  TypeId get_or_create(SymbolId symbol, celestia::semantic::TypeKind kind) {

    auto it = types_by_symbol.find(symbol);

    if (it != types_by_symbol.end()) return it->second;

    celestia::semantic::Type *type = nullptr;

    switch (kind) {

    case celestia::semantic::TypeKind::Struct: type = arena.alloc<celestia::semantic::StructType>(symbol); break;

    case celestia::semantic::TypeKind::Function: type = arena.alloc<celestia::semantic::FunctionType>(); break;

    default: return TypeId::invalid();
    }

    TypeId id = insert(type);

    types_by_symbol.emplace(symbol, id);

    return id;
  }

  TypeId get_or_create_primitive(SymbolId symbol, celestia::semantic::PrimitiveKind primitive) {

    auto it = types_by_symbol.find(symbol);

    if (it != types_by_symbol.end()) return it->second;

    auto *type = arena.alloc<celestia::semantic::PrimitiveType>(primitive);

    TypeId id = insert(type);

    types_by_symbol.emplace(symbol, id);

    return id;
  }

  TypeId get_or_create_generic_instance(SymbolId constructor, const std::vector<TypeId> &arguments) {

    for (size_t i = 0; i < types.size(); ++i) {

      const auto &base = *types[i];

      if (base.kind != celestia::semantic::TypeKind::GenericInstance) continue;

      const auto &generic = static_cast<const celestia::semantic::GenericInstanceType &>(base);

      if (generic.constructor != constructor) continue;

      if (generic.arguments != arguments) continue;

      return TypeId(static_cast<TypeId::ValueType>(i));
    }

    auto *type = arena.alloc<celestia::semantic::GenericInstanceType>(constructor, arguments);

    return insert(type);
  }

  celestia::semantic::Type &get(TypeId id) { return *types[id.index()]; }

  const celestia::semantic::Type &get(TypeId id) const { return *types[id.index()]; }

private:
  TypeId insert(celestia::semantic::Type *type) {

    TypeId id(static_cast<TypeId::ValueType>(types.size()));

    types.push_back(type);

    return id;
  }

private:
  core::memory::Arena arena;

  std::vector<celestia::semantic::Type *> types;

  std::unordered_map<SymbolId, TypeId> types_by_symbol;
};