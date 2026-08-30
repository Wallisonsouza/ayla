#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "celestia/ir/IRTable.hpp"
#include "celestia/ir/Instruction.hpp"
#include "celestia/ir/Type.hpp"
#include "celestia/ir/Value.hpp"

namespace celestia::ir {

class IRContext {
private:
  // --------------------------------------------------
  // Entities
  // --------------------------------------------------

  Table<Value, ValueId> values;
  Table<Instruction, InstructionId> instructions;

  Table<Struct, StructId> structs;
  Table<Interface, InterfaceId> interfaces;
  Table<VTable, VTableId> vtables;

  // --------------------------------------------------
  // Types
  // --------------------------------------------------

  std::vector<std::unique_ptr<Type>> types;

  std::unordered_map<StructId, TypeId> struct_types;
  std::unordered_map<InterfaceId, TypeId> interface_types;

  std::unordered_map<TypeKind, TypeId> primitive_types;
  std::unordered_map<TypeId, TypeId> array_types;
  std::unordered_map<TypeId, TypeId> pointer_types;

  // --------------------------------------------------
  // Strings
  // --------------------------------------------------

  std::vector<std::string> strings;
  std::unordered_map<std::string, StringId> string_ids;

public:
  // ==================================================
  // Struct
  // ==================================================

  StructId create_struct(StringId name) {

    return structs.create([&](StructId id) {
      return Struct{
          .id = id,
          .name = name,
      };
    });
  }

  void add_struct_field(StructId struct_id, StringId name, TypeId type) {

    if (!struct_id.is_valid() || !name.is_valid() || !type.is_valid()) { return; }

    structs.get(struct_id).fields.push_back({
        .name = name,
        .type = type,
    });
  }

  TypeId get_or_create_struct_type(StructId id) {

    if (!id.is_valid()) return TypeId::invalid();

    auto it = struct_types.find(id);

    if (it != struct_types.end()) return it->second;

    TypeId type_id = create_type(std::make_unique<StructType>(id));

    struct_types.emplace(id, type_id);

    return type_id;
  }

  // ==================================================
  // Interface
  // ==================================================

  InterfaceId create_interface(StringId name) {

    return interfaces.create([&](InterfaceId id) {
      return Interface{
          .id = id,
          .name = name,
      };
    });
  }

  void add_interface_method(InterfaceId interface_id, StringId name, TypeId type) {

    if (!interface_id.is_valid() || !name.is_valid() || !type.is_valid()) { return; }

    interfaces.get(interface_id)
        .methods.push_back({
            .name = name,
            .type = type,
        });
  }

  TypeId get_or_create_interface_type(InterfaceId id) {

    if (!id.is_valid()) return TypeId::invalid();

    auto it = interface_types.find(id);

    if (it != interface_types.end()) return it->second;

    TypeId type_id = create_type(std::make_unique<InterfaceType>(id));

    interface_types.emplace(id, type_id);

    return type_id;
  }

  // ==================================================
  // VTable
  // ==================================================

  VTableId create_vtable(InterfaceId interface_id, StructId concrete_type) {

    if (!interface_id.is_valid() || !concrete_type.is_valid()) { return VTableId::invalid(); }

    return vtables.create([&](VTableId id) {
      return VTable{
          .id = id,
          .interface_id = interface_id,
          .concrete_type = concrete_type,
      };
    });
  }

  void add_vtable_method(VTableId vtable_id, FunctionId function_id) {

    if (!vtable_id.is_valid() || !function_id.is_valid()) { return; }

    vtables.get(vtable_id).methods.push_back(function_id);
  }

  // ==================================================
  // Values
  // ==================================================

  ValueId create_value(TypeId type) {

    if (!type.is_valid()) return ValueId::invalid();

    return values.create([&](ValueId id) {
      return Value{
          .id = id,
          .type = type,
      };
    });
  }

  template <typename T> ValueId create_constant(TypeId type, T value) {

    ValueId result = create_value(type);

    if (!result.is_valid()) return ValueId::invalid();

    instructions.create([&](InstructionId id) {
      return Instruction{
          .id = id,
          .kind = InstructionKind::Constant,
          .result = result,
          .data = std::move(value),
      };
    });

    return result;
  }

  // ==================================================
  // Strings
  // ==================================================

  StringId intern_string(std::string value) {

    auto it = string_ids.find(value);

    if (it != string_ids.end()) return it->second;

    StringId id{static_cast<uint32_t>(strings.size())};

    strings.push_back(std::move(value));

    string_ids.emplace(strings.back(), id);

    return id;
  }

  // ==================================================
  // Types
  // ==================================================

  TypeId create_type(std::unique_ptr<Type> type) {

    if (!type) return TypeId::invalid();

    TypeId id{static_cast<uint32_t>(types.size())};

    types.push_back(std::move(type));

    return id;
  }

  TypeId get_or_create_type(TypeKind kind) {

    auto it = primitive_types.find(kind);

    if (it != primitive_types.end()) return it->second;

    TypeId id = create_type(std::make_unique<Type>(kind));

    primitive_types.emplace(kind, id);

    return id;
  }

  TypeId get_or_create_array(TypeId element_type) {

    if (!element_type.is_valid()) return TypeId::invalid();

    auto it = array_types.find(element_type);

    if (it != array_types.end()) return it->second;

    TypeId id = create_type(std::make_unique<ArrayType>(element_type));

    array_types.emplace(element_type, id);

    return id;
  }

  TypeId get_or_create_pointer(TypeId pointee) {

    if (!pointee.is_valid()) return TypeId::invalid();

    auto it = pointer_types.find(pointee);

    if (it != pointer_types.end()) return it->second;

    TypeId id = create_type(std::make_unique<PointerType>(pointee));

    pointer_types.emplace(pointee, id);

    return id;
  }

  // ==================================================
  // Accessors
  // ==================================================

  Value &get_value(ValueId id) { return values.get(id); }

  const Value &get_value(ValueId id) const { return values.get(id); }

  Instruction &get_instruction(InstructionId id) { return instructions.get(id); }

  const Instruction &get_instruction(InstructionId id) const { return instructions.get(id); }

  Type &get_type(TypeId id) { return *types[id.index()]; }

  const Type &get_type(TypeId id) const { return *types[id.index()]; }

  const Struct &get_struct(StructId id) const { return structs.get(id); }

  const Interface &get_interface(InterfaceId id) const { return interfaces.get(id); }

  const VTable &get_vtable(VTableId id) const { return vtables.get(id); }

  const std::string &get_string(StringId id) const { return strings[id.index()]; }

  // ==================================================
  // Counts
  // ==================================================

  TypeId create_function_type(std::vector<TypeId> parameters, TypeId return_type) {

    if (!return_type.is_valid()) return TypeId::invalid();

    return create_type(std::make_unique<FunctionType>(std::move(parameters), return_type));
  }

  size_t type_count() const { return types.size(); }

  size_t struct_count() const { return structs.size(); }

  size_t interface_count() const { return interfaces.size(); }

  size_t vtable_count() const { return vtables.size(); }

  size_t value_count() const { return values.size(); }

  size_t instruction_count() const { return instructions.size(); }
};

} // namespace celestia::ir