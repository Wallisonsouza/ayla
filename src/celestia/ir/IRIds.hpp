#pragma once

#include "celestia/core/ids/Id.hpp"

#pragma once

#include "celestia/core/ids/Id.hpp"

namespace celestia::ir {

struct TypeTag {};
struct ValueTag {};
struct FunctionTag {};
struct BlockTag {};
struct ModuleTag {};
struct StructTag {};
struct InterfaceTag {};
struct VTableTag {};
struct GlobalTag {};
struct InstructionTag {};

struct StringTag {};
using StringId = Id<StringTag>;

using TypeId = Id<TypeTag>;
using ValueId = Id<ValueTag>;
using FunctionId = Id<FunctionTag>;
using BlockId = Id<BlockTag>;
using ModuleId = Id<ModuleTag>;
using StructId = Id<StructTag>;
using InterfaceId = Id<InterfaceTag>;
using VTableId = Id<VTableTag>;
using GlobalId = Id<GlobalTag>;
using InstructionId = Id<InstructionTag>;

} // namespace celestia::ir