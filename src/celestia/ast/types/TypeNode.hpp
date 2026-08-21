#pragma once

#include "celestia/ast/Node.hpp"
#include "celestia/semantic/symbol/SymbolId.hpp"

namespace celestia::ast {

struct TypeNode : Node {


  explicit TypeNode(NodeKind kind) : Node(kind) {}
};

} // namespace celestia::ast