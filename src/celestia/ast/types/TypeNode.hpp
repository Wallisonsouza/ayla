#pragma once

#include "celestia/ast/Node.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"

namespace celestia::ast {

struct TypeNode : Node {

  SymbolId symbol_id;
  explicit TypeNode(NodeKind kind) : Node(kind) {}
};

} // namespace celestia::ast