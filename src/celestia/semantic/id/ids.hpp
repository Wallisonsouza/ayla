#pragma once

#include "celestia/core/ids/Id.hpp"

namespace celestia::semantic {
struct ModuleIdTag {};
using ModuleId = Id<ModuleIdTag>;

struct SymbolIdTag {};
using SymbolId = Id<SymbolIdTag>;

struct TypeIdTag {};
using TypeId = Id<TypeIdTag>;
} // namespace celestia::semantic
