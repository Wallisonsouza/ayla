#pragma once

#include "celestia/ast/Node.hpp"
#include "celestia/semantic/symbols/SymbolId.hpp"

namespace celestia::ast {

struct Expression : Node {

  SymbolId resolved_symbol_id;
  explicit Expression(NodeKind k) : Node(k) {}
};

} // namespace celestia::ast